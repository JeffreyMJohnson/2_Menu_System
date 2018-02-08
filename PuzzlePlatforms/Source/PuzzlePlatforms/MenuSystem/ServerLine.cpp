// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerLine.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"



void UServerLine::SetAddress(const FText& AddressIn)
{
	if (!ensure(AddressText)) return;
	AddressText->Text = AddressIn;
}

const FText UServerLine::GetAddress()
{
	if (!ensure(AddressText)) return FText();
	return AddressText->Text;
}
