// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlanetLineUWB.h"
#include "Widgets/SmallBuildingIconUWB.h"
#include "Blueprint/WidgetTree.h"
#include "Player/StarPlayerState.h"
#include "Player/StarPlayerController.h"
#include "SpaceEntities/Planet.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UPlanetLineUWB::Initialize()
{
	bool bResult = Super::Initialize();

	if (IconButton)
	{
		IconButton->OnClicked.AddDynamic(this, &UPlanetLineUWB::SnapToPlanet);
	}

	return bResult;
}

void UPlanetLineUWB::InitializePlanetLineWidget(APlanet* Planet)
{
	TargetPlanet = Planet;
	PlanetName->SetText(FText::FromString(Planet->Info.Name));
	Data->SetText(FText::AsNumber(Planet->Info.SlotsNum));

	BuildingTable->ClearChildren();
	SmallBuildingIcons.Empty();

	for (int32 i = 0; i < Planet->Buildings.Num(); i++)
	{
		USmallBuildingIconUWB* BuildingIconWidget = WidgetTree->ConstructWidget<USmallBuildingIconUWB>(SmallBuildingIconClass);

		if (BuildingIconWidget)
		{
			BuildingTable->AddChild(BuildingIconWidget);
			BuildingIconWidget->InitializeSmallBuildingIconWidget(Planet->Buildings[i]);
			SmallBuildingIcons.Add(BuildingIconWidget);
		}
	}
}

void UPlanetLineUWB::SnapToPlanet()
{
	if (AStarPlayerController* Player = Cast<AStarPlayerController>(TargetPlanet->GetOwningPlayer()->GetPlayerController()))
	{
		Player->SnapToSpaceObject(TargetPlanet);
	}
}