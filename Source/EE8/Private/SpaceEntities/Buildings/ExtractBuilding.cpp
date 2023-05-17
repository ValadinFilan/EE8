// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/ExtractBuilding.h"
#include "SpaceEntities/Planet.h"
#include "Player/StarPlayerState.h"

void UExtractBuilding::Update()
{
	Super::Update();

	OwningPlanet->GetOwningPlayer()->AddEnergyIncome(BaseProduction * (1 + GetBuildingLevelData().LevelBuff));
}

void UExtractBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);

	BuildingLevels.Add(FBuildingLevel(600, 10.0f, FName("e1")));
	BuildingLevels.Add(FBuildingLevel(1200, 20.0f, FName("e2")));
	BuildingLevels.Add(FBuildingLevel(2400, 40.0f, FName("e3")));
}
