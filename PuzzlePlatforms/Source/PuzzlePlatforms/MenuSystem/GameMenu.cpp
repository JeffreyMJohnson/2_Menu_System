// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"

#include "Components/Button.h"


bool UGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(CancelMenuButton)) return false;
	CancelMenuButton->OnClicked.AddDynamic(this, &UGameMenu::TearDown);

	if (!ensure(MainMenuButton)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UGameMenu::GoBackToMainMenu);

	return true;
}

void UGameMenu::GoBackToMainMenu()
{
	if (!ensure(MenuInterface)) return;
	TearDown();

	MenuInterface->ReturnToMainMenu();
}
