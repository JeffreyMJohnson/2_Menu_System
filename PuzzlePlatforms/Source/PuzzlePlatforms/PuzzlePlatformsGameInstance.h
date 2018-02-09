// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	const FString& MainMenuBPClassReference = TEXT("/Game/MenuSystem/WBP_MainMenu");
	const FString& GameMenuWBPClassReference = TEXT("/Game/MenuSystem/WBP_GameMenu");
	const FString& MainMenuLevelTravelUrl = TEXT("/Game/MenuSystem/MainMenu");
	const FName& SESSION_NAME = TEXT("My Session");

	UPROPERTY()
	class UMainMenu* WBP_MainMenu;

	UPROPERTY()
	class UGameMenu* WBP_GameMenu;
	
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadGameMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void DestroyGameMenu();
	
	// IMenuInterface implementation.
	UFUNCTION(Exec)
	virtual void HostGame() override;

	UFUNCTION(Exec)
	virtual void JoinGame(uint32 Indexn) override;

	UFUNCTION(Exec)
	virtual void ReturnToMainMenu();

	UFUNCTION()
	virtual void ExitGame() override;

	UFUNCTION()
	virtual void RefreshServerList() override;

	UFUNCTION()
	void NetworkError(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUserWidget> MainMenuBPClass;

	UPROPERTY()
	TSoftClassPtr<UUserWidget> GameMenuWBPClass;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;


	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void CreateSession();

	
};
