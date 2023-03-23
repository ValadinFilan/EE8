// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceEntities/Ship.h"
#include "SpaceEntities/Planet.h"
#include "StarPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEnergyIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FMetalIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FCarbonIncomeUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetAdd, APlanet);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetRemove, APlanet);

/**
 * 
 */
UCLASS()
class EE8_API AStarPlayerState : public APlayerState
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShip> SpawningShipClass;

	TArray<AShip*> PlayerShips;

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
	virtual void BeginPlay() override;

};
