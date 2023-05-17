// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CreateBuildingUWB.h"
#include "Widgets/BuildingIconUWB.h"
#include "Components/Button.h"
#include "SpaceEntities/Buildings/Building.h"
#include "SpaceEntities/Planet.h"
#include "..\..\Public\Widgets\CreateBuildingUWB.h"

void UCreateBuildingUWB::InitializeCreateBuildingWidget(APlanet* TargetPlanet, UBuildingIconUWB* TargetBuildingIconWidget)
{
	Planet = TargetPlanet;
	BuildingIconWidget = TargetBuildingIconWidget;

	BExtractButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateExtractBuilding);

	BShipyardButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateShipyardBuilding);

	BDefenceButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateDefenceBuilding);

	BManagementButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateManagementBuilding);
}

void UCreateBuildingUWB::CreateExtractBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Extract), EBuildingType::Extract, true);
}

void UCreateBuildingUWB::CreateShipyardBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Shipyard), EBuildingType::Shipyard, true);
}

void UCreateBuildingUWB::CreateDefenceBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Defence), EBuildingType::Defence, true);
}

void UCreateBuildingUWB::CreateManagementBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Management), EBuildingType::Management, true);
}