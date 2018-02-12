// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerLine.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MainMenu.h"


const FText UServerLine::GetAddress()
{
	if (!ensure(ServerNameText)) return FText();
	return ServerNameText->Text;
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
