// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Online.h"

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
		// Create new session
		FOnlineSessionSettings SessionSettings;

		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
		SessionInterface->CreateSession(0, "My Session", SessionSettings);
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

void UPuzzlePlatformsGameInstance::ExitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		PC->ConsoleCommand(TEXT("Quit"));
	}
}


