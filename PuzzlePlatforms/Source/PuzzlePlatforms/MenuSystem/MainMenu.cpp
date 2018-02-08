// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"

#include "ServerLine.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinMenuButton)) return false;
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinGameButton)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	if (!ensure(ExitButton)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface)
	{
		MenuInterface->HostGame();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(JoinMenu)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(MainMenu)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinGame()
{
	/*
	if (!ensure(IPAddressField)) return;
	if (MenuInterface)
	{
		MenuInterface->JoinGame(IPAddressField->GetText().ToString());
	}
	*/

	AddServerLine(FText::FromString("I am a server!"));

}

void UMainMenu::ExitGame()
{
	if (MenuInterface)
	{
		MenuInterface->ExitGame();
	}
}

void UMainMenu::AddServerLine(const FText ServerIn)
{
	if (!ensure(ServerLineWidgetClass)) return;
	if (!ensure(ServerListScrollBox)) return;
	
	UWorld* World = GetWorld();
	if (!ensure(World)) return;



	UServerLine* NewServerLine = CreateWidget<UServerLine>(World, ServerLineWidgetClass);
	if (!ensure(NewServerLine)) return;

	NewServerLine->SetAddress(ServerIn);

	ServerListScrollBox->AddChild(NewServerLine);
	
}
