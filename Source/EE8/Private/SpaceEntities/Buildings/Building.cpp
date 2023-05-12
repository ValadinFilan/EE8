// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Buildings/Building.h"

void UBuilding::Initialize(APlanet* Planet)
{
	OwningPlanet = Planet;
}

void UBuilding::Update()
{
}

void UBuilding::UpgrageLevel()
{
	if (Level < BuildingLevels.Num() - 1)
	{
		Level++;
	}
}

FBuildingLevel UBuilding::GetBuildingLevelData()
{
	if (Level < BuildingLevels.Num())
	{
		return BuildingLevels[Level];
	}

	return FBuildingLevel();
}

int32 UBuilding::GetBuildingLevel()
{
	return Level + 1;
}

EBuildingType UBuilding::GetBuildingType()
{
	return BuildingType;
}
