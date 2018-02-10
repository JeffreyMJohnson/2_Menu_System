// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuSystem/BaseMenu.h"

#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUserName;

	FServerData()
	{
		Name = "";
		CurrentPlayers = 0;
		MaxPlayers = 0;
		HostUserName = "";
	}
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UBaseMenu
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	UFUNCTION()
	void SetServerList(TArray<FServerData>& ServerData);

	UFUNCTION()
	void SelectIndex(uint32 Index);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UServerLine> ServerLineWidgetClass;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ServerListScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	TOptional<uint32> SelectedIndex;
	
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void AddServerLine(UWorld* World, const FServerData& Data, uint32 Index);

	void UpdateRows();
	
};
