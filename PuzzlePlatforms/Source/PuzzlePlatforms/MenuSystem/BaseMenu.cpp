// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMenu.h"

void UBaseMenu::Setup()
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

void UBaseMenu::TearDown()
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

void UBaseMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	TearDown();
}
