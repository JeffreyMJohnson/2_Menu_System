// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	const FString& MainMenuBPClassReference = TEXT("/Game/MenuSystem/WBP_MainMenu");
	const FString& GameMenuWBPClassReference = TEXT("/Game/MenuSystem/WBP_GameMenu");
	const FString& MainMenuLevelTravelUrl = TEXT("/Game/MenuSystem/MainMenu.MainMenu");

	UPROPERTY()
	class UMainMenu* WBP_MainMenu;

	UPROPERTY()
	class UGameMenu* WBP_GameMenu;
	
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadGameMenu();
	
	// IMenuInterface implementation.
	UFUNCTION(Exec)
	virtual void HostGame() override;

	UFUNCTION(Exec)
	virtual void JoinGame(const FString& IPAddress) override;

	UFUNCTION(Exec)
	virtual void ReturnToMainMenu();

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUserWidget> MainMenuBPClass;

	UPROPERTY()
	TSoftClassPtr<UUserWidget> GameMenuWBPClass;


	
};
