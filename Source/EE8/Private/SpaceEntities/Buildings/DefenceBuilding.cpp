// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/DefenceBuilding.h"

void UDefenceBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);
	BuildingLevels.Add(FBuildingLevel(10.0f, FName("d1")));
	BuildingLevels.Add(FBuildingLevel(20.0f, FName("d2")));
	BuildingLevels.Add(FBuildingLevel(40.0f, FName("d3")));
}