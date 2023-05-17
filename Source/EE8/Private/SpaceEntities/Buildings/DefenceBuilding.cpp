// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/DefenceBuilding.h"

void UDefenceBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);
	BuildingType = EBuildingType::Defence;
	BuildingLevels.Add(FBuildingLevel(600, 10.0f, FName("d1")));
	BuildingLevels.Add(FBuildingLevel(1200, 20.0f, FName("d2")));
	BuildingLevels.Add(FBuildingLevel(2400, 40.0f, FName("d3")));
}