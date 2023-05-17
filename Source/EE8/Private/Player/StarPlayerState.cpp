// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StarPlayerState.h"
#include "..\..\Public\Player\StarPlayerState.h"

AStarPlayerState::AStarPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 2.0f;
}

void AStarPlayerState::BeginPlay()
{
	Metal = 1000.0f;
	Energy = 1000.0f;
	Carbon = 0.0f;

	MetalIncome = 0.0f;
	EnergyIncome = 0.0f;
	CarbonIncome = 0.0f;

	AShip* Ship = GetWorld()->SpawnActor<AShip>(SpawningShipClass);
	Ship->Initialize(this);
	PlayerShips.Add(Ship);

}

void AStarPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(DeltaTime));
	Metal += MetalIncome;
	OnMetalUpdate.Broadcast(Metal);
	Energy += EnergyIncome;
	OnEnergyUpdate.Broadcast(Energy);
	Carbon += CarbonIncome;
	OnCarbonUpdate.Broadcast(Carbon);
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
		Planet->SetOwningPlayer(this);
		OnPlanetAdd.Broadcast(Planet);
	}
}

void AStarPlayerState::RenewCapturedPlanet(APlanet* Planet)
{
	OnPlanetRenew.Broadcast(Planet);
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