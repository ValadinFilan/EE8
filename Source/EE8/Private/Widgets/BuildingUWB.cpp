// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/BuildingUWB.h"
#include "SpaceEntities/Buildings/Building.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UBuildingUWB::InitializeBuildingWidget()
{
	BuildingNameMainTextBox->SetText(FText::FromString("NAMEE"));
}

void UBuildingUWB::InitializeBuildingWidget(UBuilding* Building)
{
	BuildingNameMainTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));
	BuildingNameTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));
}
