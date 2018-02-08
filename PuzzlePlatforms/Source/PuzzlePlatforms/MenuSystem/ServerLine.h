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
	//virtual bool Initialize() override;
	void SetAddress(const FText& AddressIn);
	const FText GetAddress();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* AddressButton;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AddressText;
	
};
