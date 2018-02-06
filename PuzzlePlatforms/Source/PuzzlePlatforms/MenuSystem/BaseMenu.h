// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"

#include "BaseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UBaseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(IMenuInterface* MenuInterfaceIn) { MenuInterface = MenuInterfaceIn; }

	UFUNCTION()
	void Setup();

	UFUNCTION()
	void TearDown();

protected:
	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

	IMenuInterface* MenuInterface;
	
	
};
