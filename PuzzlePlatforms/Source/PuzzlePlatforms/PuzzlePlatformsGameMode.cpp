// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformsGameMode.h"
#include "PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//SetActorTickEnabled(true);
}


void APuzzlePlatformsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	/**/
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!ensure(PC)) return;
	

}
