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
class APlanet;

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
	float MeanPlanetsInterval = 600.f;

	UPROPERTY(EditDefaultsOnly)
	float MinDistanceToStar= 500.f;
};

UCLASS()
class EE8_API AStar : public ASpaceObject
{
	GENERATED_BODY()

protected:

	ULineBatchComponent* LBComponent;
	FLinearColor DrawColor = FLinearColor(1, 1, 1);
	FRandomStream RStream;

	UPROPERTY()
	TArray<FVector> Neighbours;

	UPROPERTY(EditDefaultsOnly)
	FSystemParameters Parameters;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlanet> PlanetClass;

	void DrawConnectionWithStars();

	/// <summary>
	/// generate orbit and planet using kepler parameters
	/// </summary>
	/// <param name="SemiMajorAxis">[0, inf]</param>
	/// <param name="Eccentricity">[0,1)</param>
	/// <param name="Inclination">[-360, 360]</param>
	/// <param name="LongitudeofAN">[-360, 360]</param>
	/// <returns>pointer to a planet</returns>
	APlanet* GeneratePlanet(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN);

	TArray<APlanet*> Planets;

	static double RandNormDist(double U1, double U2, double mu, double sigma);

public:
	AStar();

	void Initialize(int32 PlanetCount, TArray<FVector> NearestNeighbours);

	void SpawnPlanets();

};
