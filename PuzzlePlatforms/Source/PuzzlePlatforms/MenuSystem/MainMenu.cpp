// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"



bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(Host)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HandleHostOnClickEvent);

	if (!ensure(Join)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::HandleJoinOnClickEvent);

	return true;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!ensure(PC)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	if (UWorld* World = GetWorld())
	{
		this->RemoveFromViewport();

		APlayerController* PC = World->GetFirstPlayerController();
		if (!ensure(PC)) return;

		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

void UMainMenu::HandleHostOnClickEvent()
{
	if (MenuInterface)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::HandleJoinOnClickEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Join button clicked..."));
}
