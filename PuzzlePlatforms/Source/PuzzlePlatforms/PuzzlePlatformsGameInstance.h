// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly)
	FString MainMenuBPClassReference;

	UPROPERTY()
	class UUserWidget* WBP_MainMenu;

	virtual void Init() override;
	
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Connect(FString Address);

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUserWidget> MainMenuBPClass;
	
};
