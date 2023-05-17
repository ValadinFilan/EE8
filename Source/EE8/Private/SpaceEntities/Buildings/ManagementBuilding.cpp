// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/ManagementBuilding.h"

void UManagementBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);
	BuildingLevels.Add(FBuildingLevel(10.0f, FName("m1")));
	BuildingLevels.Add(FBuildingLevel(20.0f, FName("m2")));
	BuildingLevels.Add(FBuildingLevel(40.0f, FName("m3")));
}