// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StarPlayerState.h"
#include "..\..\Public\Player\StarPlayerState.h"

void AStarPlayerState::BeginPlay()
{
	Metal = 1000;
	Energy = 1000;
	Carbon = 0;

	MetalIncome = 0.0f;
	EnergyIncome = 0.0f;
	CarbonIncome = 0.0f;

	AShip* Ship = GetWorld()->SpawnActor<AShip>(SpawningShipClass);
	Ship->Initialize(this);
	PlayerShips.Add(Ship);
}

void AStarPlayerState::AddEnergyIncome(float Increment)
{
	EnergyIncome += Increment;
	if (EnergyIncome < 0) EnergyIncome = 0;
	OnEnergyIncomeUpdate.Broadcast(EnergyIncome);
}

void AStarPlayerState::AddMetalIncome(float Increment)
{
	MetalIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnMetalIncomeUpdate.Broadcast(MetalIncome);
}

void AStarPlayerState::AddCarbonIncome(float Increment)
{
	CarbonIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnCarbonIncomeUpdate.Broadcast(CarbonIncome);
}

void AStarPlayerState::AddCapturedPlanet(APlanet* Planet)
{
	if (Planet && !PlayerPlanets.Contains(Planet))
	{
		PlayerPlanets.Add(Planet);
		OnPlanetAdd.Broadcast(Planet);
	}
}

void AStarPlayerState::RemoveCapturedPlanet(APlanet* Planet)
{
	if (Planet && PlayerPlanets.Contains(Planet))
	{
		PlayerPlanets.Remove(Planet);
		OnPlanetRemove.Broadcast(Planet);
	}
}

void AStarPlayerState::AddShip(AShip* Ship)
{
	if (Ship && PlayerShips.Contains(Ship))
	{
		PlayerShips.Remove(Ship);
		OnShipAdd.Broadcast(Ship);
	}
}

void AStarPlayerState::RemoveShip(AShip* Ship)
{
	if (Ship && PlayerShips.Contains(Ship))
	{
		PlayerShips.Remove(Ship);
		OnShipRemove.Broadcast(Ship);
	}
}