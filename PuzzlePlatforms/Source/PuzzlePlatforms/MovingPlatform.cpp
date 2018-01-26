// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	PlatformStartLocation = GetActorLocation();
	TargetStartLocation = GetTransform().TransformPosition(TargetLocation);
	TotalTravelDistance = (TargetStartLocation - PlatformStartLocation).Size();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	bool bIsActive = ActiveTriggers > 0;

	if (bIsActive && HasAuthority())
	{
		if ((PlatformStartLocation - GetActorLocation()).Size() > TotalTravelDistance)
		{
			//move actor to the target location
			SetActorLocation(TargetStartLocation);

			//swap target and start
			FVector Temp = PlatformStartLocation;
			PlatformStartLocation = TargetStartLocation;
			TargetStartLocation = Temp;
		}

		FVector NewLocation = GetActorLocation();
		MoveDirection = (TargetStartLocation - PlatformStartLocation).GetSafeNormal();

		NewLocation += MoveDirection * MoveSpeed * DeltaSeconds;
		SetActorLocation(NewLocation);
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
	
}
