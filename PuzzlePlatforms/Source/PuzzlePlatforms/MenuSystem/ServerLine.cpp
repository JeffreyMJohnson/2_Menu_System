// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerLine.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MainMenu.h"



void UServerLine::SetAddress(const FText& AddressIn)
{
	if (!ensure(AddressText)) return;
	AddressText->Text = AddressIn;
}

void UServerLine::SetNumPlayers(const uint16 NumPlayers, const uint16 MaxPlayers)
{
	if (!ensure(NumPlayersText)) return;

	FString Formatted = FString::Printf(TEXT("%d / %d"), NumPlayers, MaxPlayers);
	NumPlayersText->SetText(FText::FromString(Formatted));
}

const FText UServerLine::GetAddress()
{
	if (!ensure(AddressText)) return FText();
	return AddressText->Text;
}

void UServerLine::Setup(class UMainMenu* Parent, uint32 Index)
{
	this->Parent = Parent;
	this->Index = Index;

	if (!ensure(AddressButton)) return;

	AddressButton->OnClicked.AddDynamic(this, &UServerLine::HandleOnClick);
}

void UServerLine::HandleOnClick()
{
	if (Parent)
	{
		Parent->SelectIndex(Index);
	}
}
