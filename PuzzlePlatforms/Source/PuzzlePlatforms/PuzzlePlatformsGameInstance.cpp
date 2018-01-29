// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

#include "MenuSystem/MainMenu.h"

#include "PlatformTrigger.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	/**/
	MainMenuBPClassReference = TEXT("/Game/MenuSystem/WBP_MainMenu");
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClass(*MainMenuBPClassReference);
	if (!ensure(MainMenuClass.Class)) return;
	MainMenuBPClass = MainMenuClass.Class;
	
	//UE_LOG(LogTemp, Warning, TEXT("Found class: %s"), *MainMenuBPClass.Class->GetName());

}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Menu class saved: %s"), *MainMenuBPClass.GetAssetName());

}


void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	WBP_MainMenu = CreateWidget<UMainMenu>(this, MainMenuBPClass.Get());
	if (!ensure(WBP_MainMenu)) return;

	WBP_MainMenu->SetMenuInterface(this);

	WBP_MainMenu->Setup();
}

void UPuzzlePlatformsGameInstance::Host()
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

void UPuzzlePlatformsGameInstance::Connect(FString Address)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Connecting to %s"), *Address));

		UWorld* World = GetWorld();
		if (!ensure(World)) return;

		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
}
