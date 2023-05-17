// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/ShipyardBuilding.h"

void UShipyardBuilding::Initialize(APlanet* Planet)
{
	Super::Initialize(Planet);
	BuildingLevels.Add(FBuildingLevel(10.0f, FName("s1")));
	BuildingLevels.Add(FBuildingLevel(20.0f, FName("s2")));
	BuildingLevels.Add(FBuildingLevel(40.0f, FName("s3")));
}