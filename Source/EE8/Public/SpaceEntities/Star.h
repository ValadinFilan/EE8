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
	float MinDistanceToStar = 500.f;
};

USTRUCT(BlueprintType)
struct FOrbitParameters
{
	GENERATED_BODY()

public:

	FOrbitParameters() {}

	FOrbitParameters(float SMA, float Ecc, float Inc, float LAN, float TA)
	{
		SemiMajorAxis = SMA;
		Eccentricity = Ecc;
		Inclination = Inc;
		LongitudeofAN = LAN;
		TrueAnomaly = TA;
	}

	UPROPERTY(EditDefaultsOnly)
		float SemiMajorAxis;

	UPROPERTY(EditDefaultsOnly)
		float Eccentricity;

	UPROPERTY(EditDefaultsOnly)
		float Inclination;

	UPROPERTY(EditDefaultsOnly)
		float LongitudeofAN;

	UPROPERTY(EditDefaultsOnly)
		float TrueAnomaly;
};

UCLASS()
class EE8_API AStar : public ASpaceObject
{
	GENERATED_BODY()

protected:

	ULineBatchComponent* LBComponent;
	FLinearColor DrawColor = FLinearColor(1, 1, 1);
	FRandomStream RStream;

	UPROPERTY(EditDefaultsOnly)
	FSystemParameters Parameters;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlanet> PlanetClass;

	/// <summary>
	/// generate orbit and planet using kepler parameters
	/// </summary>
	/// <param name="SemiMajorAxis">[0, inf]</param>
	/// <param name="Eccentricity">[0,1)</param>
	/// <param name="Inclination">[-360, 360]</param>
	/// <param name="LongitudeofAN">[-360, 360]</param>
	/// <param name="TrueAnomaly">[-PI, PI]</param>
	/// <returns>pointer to a planet</returns>
	FTransform GeneratePlanetTransform(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN, float TrueAnomaly);

	TArray<APlanet*> Planets;

	TArray<FOrbitParameters> Orbits;

	static double RandNormDist(double U1, double U2, double mu, double sigma);

public:
	AStar();

	void Initialize(int32 PlanetCount);

	void SpawnPlanets();

	UPROPERTY(EditDefaultsOnly)
	bool PlanetsVisibility = false;

	UFUNCTION(BlueprintCallable)
	void SetPlanetsVisibility(bool Visibility);

	UFUNCTION(BlueprintCallable)
	bool GetPlanetsVisibility();

};