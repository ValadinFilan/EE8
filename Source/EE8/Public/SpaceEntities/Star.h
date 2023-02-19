// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Star.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API AStar : public ASpaceObject
{
	GENERATED_BODY()


protected:

	UPROPERTY()
	int32 CountOfPlanets;

public:
	
	void Initialize(int32 PlanetCount);

	int32 GetCountOfPlanets();
};
