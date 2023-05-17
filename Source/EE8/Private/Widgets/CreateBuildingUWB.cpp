// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CreateBuildingUWB.h"
#include "Widgets/BuildingIconUWB.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SpaceEntities/Buildings/Building.h"
#include "SpaceEntities/Planet.h"
#include "Player/StarPlayerState.h"
#include "..\..\Public\Widgets\CreateBuildingUWB.h"

void UCreateBuildingUWB::InitializeCreateBuildingWidget(APlanet* TargetPlanet, UBuildingIconUWB* TargetBuildingIconWidget)
{
	Planet = TargetPlanet;
	BuildingIconWidget = TargetBuildingIconWidget;

	BExtractButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateExtractBuilding);

	BShipyardButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateShipyardBuilding);

	BDefenceButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateDefenceBuilding);

	BManagementButton->OnClicked.AddUniqueDynamic(this, &UCreateBuildingUWB::CreateManagementBuilding);

	//TargetPlanet->GetOwningPlayer()->OnMetalUpdate.Clear();
	TargetPlanet->GetOwningPlayer()->OnMetalUpdate.AddUObject(this, &UCreateBuildingUWB::UpdateMetal);//possible trouble

	//TargetPlanet->GetOwningPlayer()->OnEnergyUpdate.Clear();
	TargetPlanet->GetOwningPlayer()->OnEnergyUpdate.AddUObject(this, &UCreateBuildingUWB::UpdateEnergy);

	//TargetPlanet->GetOwningPlayer()->OnCarbonUpdate.Clear();
	TargetPlanet->GetOwningPlayer()->OnCarbonUpdate.AddUObject(this, &UCreateBuildingUWB::UpdateCarbon);
}

void UCreateBuildingUWB::CreateExtractBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Extract), true);
}

void UCreateBuildingUWB::CreateShipyardBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Shipyard), true);
}

void UCreateBuildingUWB::CreateDefenceBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Defence), true);
}

void UCreateBuildingUWB::CreateManagementBuilding()
{
	BuildingIconWidget->InitializeIconWidget(Planet->CreateBuilding(EBuildingType::Management), true);
}

void UCreateBuildingUWB::UpdateMetal(float NewMetal)
{
	Metal->SetText(FText::AsNumber(NewMetal));
}

void UCreateBuildingUWB::UpdateEnergy(float NewEnergy)
{
	Energy->SetText(FText::AsNumber(NewEnergy));
}

void UCreateBuildingUWB::UpdateCarbon(float NewCarbon)
{
	Carbon->SetText(FText::AsNumber(NewCarbon));
}
