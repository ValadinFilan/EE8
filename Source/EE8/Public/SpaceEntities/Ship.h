// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Ship.generated.h"

class AStarPlayerState;

/**
 * 
 */
UCLASS()
class EE8_API AShip : public ASpaceObject
{
	AShip();

	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds);

	void Initialize(AStarPlayerState* PlayerState);

	UPROPERTY(EditDefaultsOnly)
	float Velocity;

	UPROPERTY(EditDefaultsOnly)
	float AvaliableOrbit;

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ASpaceObject> ConnectionTraget;

	void GoTo(ASpaceObject* Target);

	AStarPlayerState* OwningPlayerState;

	TWeakObjectPtr<ASpaceObject> TargetSpaceObject;
};
