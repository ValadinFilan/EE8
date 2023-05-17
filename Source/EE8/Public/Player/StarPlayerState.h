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
DECLARE_MULTICAST_DELEGATE_OneParam(FEnergyUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FMetalUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FCarbonUpdate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetAdd, APlanet*);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetRenew, APlanet*);
DECLARE_MULTICAST_DELEGATE_OneParam(FPlanetRemove, APlanet*);
DECLARE_MULTICAST_DELEGATE_OneParam(FShipAdd, AShip*);
DECLARE_MULTICAST_DELEGATE_OneParam(FShipRemove, AShip*);

/**
 * 
 */
UCLASS()
class EE8_API AStarPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	float Energy;

	UPROPERTY(VisibleAnywhere)
	float Metal;

	UPROPERTY(VisibleAnywhere)
	float Carbon;

	UPROPERTY(VisibleAnywhere)
	float EnergyIncome;

	UPROPERTY(VisibleAnywhere)
	float MetalIncome;

	UPROPERTY(VisibleAnywhere)
	float CarbonIncome;
	
	UPROPERTY(VisibleAnywhere)
	TArray<APlanet*> CapturedPlanets;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShip> SpawningShipClass;

	UPROPERTY(VisibleAnywhere)
	TArray<AShip*> PlayerShips;

	UPROPERTY(VisibleAnywhere)
	TArray<APlanet*> PlayerPlanets;

	FEnergyIncomeUpdate OnEnergyIncomeUpdate;
	FMetalIncomeUpdate OnMetalIncomeUpdate;
	FCarbonIncomeUpdate OnCarbonIncomeUpdate;
	FEnergyUpdate OnEnergyUpdate;
	FMetalUpdate OnMetalUpdate;
	FCarbonUpdate OnCarbonUpdate;
	FPlanetAdd OnPlanetAdd;
	FPlanetRenew OnPlanetRenew;
	FPlanetRemove OnPlanetRemove;
	FShipAdd OnShipAdd;
	FShipRemove OnShipRemove;

	AStarPlayerState();

	void AddEnergyIncome(float Increment);

	void AddMetalIncome(float Increment);

	void AddCarbonIncome(float Increment);

	void AddCapturedPlanet(APlanet* Planet);

	void RenewCapturedPlanet(APlanet* Planet);

	void RemoveCapturedPlanet(APlanet* Planet);

	void AddShip(AShip* Ship);
	
	void RemoveShip(AShip* Ship);
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
