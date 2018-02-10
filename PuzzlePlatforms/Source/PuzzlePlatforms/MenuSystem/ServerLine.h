// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerLine.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerLine : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected = false;

	void SetAddress(const FText& AddressIn);
	void SetNumPlayers(const uint16 NumPlayers, const uint16 MaxPlayers);

	const FText GetAddress();

	void Setup(class UMainMenu* Parent, uint32 Index);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* AddressButton;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AddressText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NumPlayersText;

	UPROPERTY()
	UMainMenu* Parent;
	uint32 Index = 0;

	UFUNCTION()
	void HandleOnClick();
};
