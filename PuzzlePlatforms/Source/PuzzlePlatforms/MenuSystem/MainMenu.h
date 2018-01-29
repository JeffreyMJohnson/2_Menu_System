// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetMenuInterface(IMenuInterface* MenuInterfaceIn) { MenuInterface = MenuInterfaceIn; }

	UFUNCTION()
	void Setup();

protected:
	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	IMenuInterface* MenuInterface;
	
	UFUNCTION()
	void HandleHostOnClickEvent();

	UFUNCTION()
	void HandleJoinOnClickEvent();
	
	
};
