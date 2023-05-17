// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/BuildingUWB.h"
#include "SpaceEntities/Planet.h"
#include "SpaceEntities/Buildings/Building.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UBuildingUWB::InitializeBuildingWidget()
{
	BuildingNameMainTextBox->SetText(FText::FromString("NAMEE"));
}

void UBuildingUWB::InitializeBuildingWidget(UBuilding* TargetBuilding)
{
	Building = TargetBuilding;
	BuildingNameMainTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));// 0xC0000005: нарушение прав доступа при чтении по адресу 0x000000000002DF30.
	BuildingNameTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));//Вызвано исключение: нарушение доступа для чтения. DelegateInstance было 0x100000000.
	BuildingLevelTextBox->SetText(FText::AsNumber(Building->GetBuildingLevel()));
	UpgradeCostTextBox->SetText(FText::AsNumber(Building->GetBuildingLevelData().UpgpadeCost));

	UpgradeButton->OnClicked.AddUniqueDynamic(this, &UBuildingUWB::BuildingWidgetUpgrade);
}

void UBuildingUWB::BuildingWidgetUpgrade()
{
	Building->OwningPlanet->UpgradeBuilding(Building);
	BuildingNameMainTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));
	BuildingNameTextBox->SetText(FText::FromName(Building->GetBuildingLevelData().BuildingName));
	BuildingLevelTextBox->SetText(FText::AsNumber(Building->GetBuildingLevel()));
	UpgradeCostTextBox->SetText(FText::AsNumber(Building->GetBuildingLevelData().UpgpadeCost));
}
