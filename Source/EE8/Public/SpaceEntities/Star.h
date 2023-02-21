// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/LineBatchComponent.h"
#include "SpaceEntities/SpaceObject.h"
#include "Engine/Engine.h"
#include <math.h>
#include "SpaceEntities/NormDistrGenerator.h"
#include "Star.generated.h"

/**
 * 
 */
class APlanet;
class NormDistrGenerator;

USTRUCT(BlueprintType)
struct FSystemParameters
{
	GENERATED_BODY()

public:

	FSystemParameters() {}

	UPROPERTY(EditDefaultsOnly)
		int32 MinPlanetNum = 1;

	UPROPERTY(EditDefaultsOnly)
		int32 MaxPlanetNum = 8;

	UPROPERTY(EditDefaultsOnly)
		float MeanPlanetsInterval = 600;
};

UCLASS()
class EE8_API AStar : public ASpaceObject
{
	GENERATED_BODY()

	ULineBatchComponent* LBComponent;
	FColor DrawColor;
	FRandomStream RStream;
	NormDistrGenerator NormGen;

protected:

	UPROPERTY()

	TArray<FVector> Neighbours;

	UPROPERTY(EditDefaultsOnly)
	FSystemParameters Parameters;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlanet> PlanetClass;

	void DrawL(); 
	
	APlanet* GeneratePlanet(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN);

	TArray<APlanet*> Planets;

public:
	AStar();

	void Initialize(int32 PlanetCount, TArray<FVector> NearestNeighbours);

	void SpawnPlanets();

};
