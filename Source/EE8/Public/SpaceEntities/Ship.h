// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Ship.generated.h"

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

	UPROPERTY(EditDefaultsOnly)
	float Velocity;

	UPROPERTY(EditDefaultsOnly)
	float AvaliableOrbit;

	void GoTo(ASpaceObject* Target);

	TWeakObjectPtr<ASpaceObject> TargetSpaceObject;
};
