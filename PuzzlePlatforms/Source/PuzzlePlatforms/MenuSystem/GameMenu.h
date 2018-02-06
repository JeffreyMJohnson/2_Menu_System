// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuSystem/BaseMenu.h"

#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenu : public UBaseMenu
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void GoBackToMainMenu();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelMenuButton;


	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
	
};
