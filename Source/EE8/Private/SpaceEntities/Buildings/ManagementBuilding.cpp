// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/ManagementBuilding.h"

void UManagementBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);
	BuildingType = EBuildingType::Management;
	BuildingLevels.Add(FBuildingLevel(600, 10.0f, FName("m1")));
	BuildingLevels.Add(FBuildingLevel(1200, 20.0f, FName("m2")));
	BuildingLevels.Add(FBuildingLevel(2400, 40.0f, FName("m3")));
}