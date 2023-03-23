// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceEntities/Planet.h"
#include "SpacePlayerState.generated.h"

class APlanet;

DECLARE_MULTICAST_DELEGATE_OneParam(FEnergyIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FMetalIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FCarbonIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetAdd, APlanet);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetRemove, APlanet);

/**
 * 
 */
UCLASS()
class EE8_API ASpacePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int64 Energy;

	int64 Metal;

	int64 Carbon;

	float EnergyIncome;

	float MetalIncome;

	float CarbonIncome;

	TArray<APlanet*> CapturedPlanets;

	//TArray<SpaceShipClass*> SpaceShips;

	//TArray<LostResourcesClass / AActor*> LostResources;

	FEnergyIncomeUpdate OnEnergyIncomeUpdate;
	FMetalIncomeUpdate OnMetalIncomeUpdate;
	FCarbonIncomeUpdate OnCarbonIncomeUpdate;
	FPlanetAdd OnPlanetAdd;
	FPlanetRemove OnPlanetRemove;

	float AddEnergyIncome(float Increment);

	float AddMetalIncome(float Increment);

	float AddCarbonIncome(float Increment);

	TArray<APlanet*> AddCapturedPlanet(APlanet Planet);

	TArray<APlanet*> RemoveCapturedPlanet(APlanet Planet);
};
