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
	if (!ensure(MenuInterface)) return;
	if (!ensure(ServerListScrollBox)) return;

	ServerListScrollBox->ClearChildren();

	MenuInterface->RefreshServerList();

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher)) return;
	if (!ensure(MainMenu)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::SetServerList(TArray<FString>& ServerNames)
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	if (!ensure(ServerListScrollBox)) return;

	ServerListScrollBox->ClearChildren();

	uint32 CurrentIndex = 0;
	for (FString& ServerName : ServerNames)
	{
		AddServerLine(World, FText::FromString(ServerName), CurrentIndex);
		++CurrentIndex;
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

void UMainMenu::JoinGame()
{
	if (SelectedIndex.IsSet() && MenuInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is %d."), SelectedIndex.GetValue());
		MenuInterface->JoinGame(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is not set."));
	}	
}

void UMainMenu::ExitGame()
{
	if (MenuInterface)
	{
		MenuInterface->ExitGame();
	}
}

void UMainMenu::AddServerLine(UWorld* World, const FText ServerIn, uint32 Index)
{
	if (!ensure(ServerLineWidgetClass)) return;
	if (!ensure(ServerListScrollBox)) return;
	
	if (World)
	{
		UServerLine* NewServerLine = CreateWidget<UServerLine>(World, ServerLineWidgetClass);
		if (!ensure(NewServerLine)) return;

		NewServerLine->SetAddress(ServerIn);
		NewServerLine->Setup(this, Index);

		ServerListScrollBox->AddChild(NewServerLine);
	}

	
}
