// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TimerManager.h"

#include "PuzzlePlatformsGameInstance.h"

const int START_SESSION_TIMER = 10;

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("PostLogin fired in GameMode."));

	++PlayerCount;

	if (PlayerCount == 3)
	{
		GetWorldTimerManager().SetTimer(SessionStartTimerHandle, this, &ALobbyGameMode::StartGameSession, START_SESSION_TIMER, false);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogTemp, Warning, TEXT("Logout fired in GameMode."));

	--PlayerCount;
}

void ALobbyGameMode::StartGameSession()
{
	if (UWorld* World = GetWorld())
	{
		if (UPuzzlePlatformsGameInstance* GI = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()))
		{
			GI->StartSession();
		}
		bUseSeamlessTravel = true;
		World->ServerTravel(TEXT("/Game/PuzzlePlatforms/Maps/Game?listen"), true, false);
	}
}
