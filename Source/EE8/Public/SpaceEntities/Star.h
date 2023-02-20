// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/LineBatchComponent.h"
#include "SpaceEntities/SpaceObject.h"
#include "Engine/Engine.h"
#include "Star.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API AStar : public ASpaceObject
{
	GENERATED_BODY()

	ULineBatchComponent* LBComponent;
	FRandomStream RStream;

protected:

	UPROPERTY()

	TArray<FVector> Neighbours;

public:
	AStar();

	void Initialize(int32 PlanetCount, TArray<FVector> NearestNeighbours);

	void DrawL();
};
