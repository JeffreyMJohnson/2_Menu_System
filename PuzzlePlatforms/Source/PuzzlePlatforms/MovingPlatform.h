// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();
	
protected:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY()
	FVector MoveDirection;

private:
	FVector PlatformStartLocation;
	FVector TargetStartLocation;
	float TotalTravelDistance;

	UPROPERTY( EditAnywhere )
	int ActiveTriggers = 1;
};
