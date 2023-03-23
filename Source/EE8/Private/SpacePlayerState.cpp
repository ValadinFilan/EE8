// Fill out your copyright notice in the Description page of Project Settings.

#include "SpacePlayerState.h"

float ASpacePlayerState::AddEnergyIncome(float Increment)
{
	EnergyIncome += Increment;
	if (EnergyIncome < 0) EnergyIncome = 0;
	OnEnergyIncomeUpdate.Broadcast(EnergyIncome);
	return EnergyIncome;
}

float ASpacePlayerState::AddMetalIncome(float Increment)
{
	MetalIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnMetalIncomeUpdate.Broadcast(MetalIncome);
	return MetalIncome;
}

float ASpacePlayerState::AddCarbonIncome(float Increment)
{
	CarbonIncome += Increment;
	if (MetalIncome < 0) MetalIncome = 0;
	OnCarbonIncomeUpdate.Broadcast(CarbonIncome);
	return CarbonIncome;
}

TArray<APlanet*> ASpacePlayerState::AddCapturedPlanet(APlanet Planet)
{
	if(!CapturedPlanets.Contains(&Planet))
		CapturedPlanets.Add(&Planet);
	//OnPlanetAdd.Broadcast(Planet);
	return CapturedPlanets;
}

TArray<APlanet*> ASpacePlayerState::RemoveCapturedPlanet(APlanet Planet)
{
	if (CapturedPlanets.Contains(&Planet))
		CapturedPlanets.Remove(&Planet);
	//OnPlanetRemove.Broadcast(Planet);
	return CapturedPlanets;
}
