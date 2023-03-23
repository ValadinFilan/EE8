// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StarPlayerState.h"

void AStarPlayerState::BeginPlay()
{
	AShip* Ship = GetWorld()->SpawnActor<AShip>(SpawningShipClass);
	PlayerShips.Add(Ship);
}

float AStarPlayerState::AddEnergyIncome(float Increment)
{
	EnergyIncome += Increment;
	if (EnergyIncome < 0) EnergyIncome = 0;
	OnEnergyIncomeUpdate.Broadcast(EnergyIncome);
	return EnergyIncome;
}

float AStarPlayerState::AddMetalIncome(float Increment)
{
	MetalIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnMetalIncomeUpdate.Broadcast(MetalIncome);
	return MetalIncome;
}

float AStarPlayerState::AddCarbonIncome(float Increment)
{
	CarbonIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnCarbonIncomeUpdate.Broadcast(CarbonIncome);
	return CarbonIncome;
}

TArray<APlanet*> AStarPlayerState::AddCapturedPlanet(APlanet Planet)
{
	if (!CapturedPlanets.Contains(&Planet))
		CapturedPlanets.Add(&Planet);
	//OnPlanetAdd.Broadcast(Planet);
	return CapturedPlanets;
}

TArray<APlanet*> AStarPlayerState::RemoveCapturedPlanet(APlanet Planet)
{
	if (CapturedPlanets.Contains(&Planet))
		CapturedPlanets.Remove(&Planet);
	//OnPlanetRemove.Broadcast(Planet);
	return CapturedPlanets;
}
