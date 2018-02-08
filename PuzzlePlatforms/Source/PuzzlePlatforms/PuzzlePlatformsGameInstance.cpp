// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Online.h"
#include "OnlineSessionSettings.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

#include "PlatformTrigger.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClass(*MainMenuBPClassReference);
	if (!ensure(MainMenuClass.Class)) return;
	MainMenuBPClass = MainMenuClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> GameMenuClass(*GameMenuWBPClassReference);
	if (!ensure(GameMenuClass.Class)) return;
	GameMenuWBPClass = GameMenuClass.Class;

}


void UPuzzlePlatformsGameInstance::Init()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine)) return;
	
	Engine->NetworkFailureEvent.AddUObject(this, &UPuzzlePlatformsGameInstance::NetworkError);

	IOnlineSubsystem* IOS = IOnlineSubsystem::Get();
	FString result = IOS == nullptr ? TEXT("nullptr") : IOS->GetSubsystemName().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Online subsystem returned %s"), *result);
	if (IOS)
	{
		SessionInterface = IOS->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);

			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch.IsValid())
			{
				SessionSearch->bIsLanQuery = true;
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	
	WBP_MainMenu = CreateWidget<UMainMenu>(this, MainMenuBPClass.Get());
	if (!ensure(WBP_MainMenu)) return;

	WBP_MainMenu->SetMenuInterface(this);

	WBP_MainMenu->Setup();
	/**/
}


void UPuzzlePlatformsGameInstance::LoadGameMenu()
{
	WBP_GameMenu = CreateWidget<UGameMenu>(this, GameMenuWBPClass.Get());
	if (!ensure(WBP_GameMenu)) return;

	WBP_GameMenu->SetMenuInterface(this);

	WBP_GameMenu->Setup();
}


void UPuzzlePlatformsGameInstance::DestroyGameMenu()
{
	if (WBP_GameMenu)
	{
		WBP_GameMenu->TearDown();
		WBP_GameMenu = nullptr;
	}
}

void UPuzzlePlatformsGameInstance::HostGame()
{
	
	if (SessionInterface.IsValid())
	{
		// Close session if already exists. Return because need to wait for complete callback which will call this method again.
		if (FNamedOnlineSession* NamedSession = SessionInterface->GetNamedSession(SESSION_NAME))
		{
			SessionInterface->DestroySession(SESSION_NAME);
			return;
		}
		else
		{
			//otherwise create new one.
			CreateSession();
		}
	}		
}


void UPuzzlePlatformsGameInstance::JoinGame(const FString& IPAddress)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Connecting to %s"), *IPAddress));

		UWorld* World = GetWorld();
		if (!ensure(World)) return;

		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			PC->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UPuzzlePlatformsGameInstance::ReturnToMainMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		PC->ClientTravel(MainMenuLevelTravelUrl, ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::NetworkError(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	ReturnToMainMenu();
}


void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hosting..."));

			if (UWorld* World = GetWorld())
			{
				World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"), true, false);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create a session."));
	}
}


void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		CreateSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to destroy session [%s]"), *SessionName.ToString());
	}
	
}


void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (SessionSearch.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found %d sessions:"), SessionSearch->SearchResults.Num());

			for (auto result : SessionSearch->SearchResults)
			{
				FString SessionId = result.GetSessionIdStr();
				UE_LOG(LogTemp, Warning, TEXT("session Id: %s"), *SessionId);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Finding sessions failed."));
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		// Create new session
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::ExitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		PC->ConsoleCommand(TEXT("Quit"));
	}
}


