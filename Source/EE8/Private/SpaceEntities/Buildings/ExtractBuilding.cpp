// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/ExtractBuilding.h"
#include "SpaceEntities/Planet.h"
#include "Player/StarPlayerState.h"

void UExtractBuilding::Update()
{
	Super::Update();

	OwningPlanet->GetOwningPlayer()->AddEnergyIncome(BaseProduction * (1 + GetBuildingLevelData().LevelBuff));
}