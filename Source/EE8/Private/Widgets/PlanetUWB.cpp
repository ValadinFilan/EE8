// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlanetUWB.h"
#include "Widgets/BuildingIconUWB.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "SpaceEntities/Planet.h"
#include "Components/NamedSlot.h"
#include "Engine/Engine.h"
//#include "Components/RichTextBlock.h"

#include "Components/Button.h"

void UPlanetUWB::InitializePlanetWidget(APlanet* Planet)
{
	PlanetNameMainTextBox->SetText(FText::FromString(Planet->Info.Name));
	PlanetDescTextBox->SetText(Planet->Info.Description);
	PlanetNameTextBox->SetText(FText::FromString(Planet->Info.Name));
	PlanetPopulationTextBox->SetText(FText::AsNumber(Planet->Info.Population));
	PlanetResourcesMetalTextBox->SetText(FText::AsNumber(Planet->Info.MetalRemaining));
	PlanetResourcesCarbonTextBox->SetText(FText::AsNumber(Planet->Info.CarbonRemaining));
	PlanetSlotNum->SetText(FText::AsNumber(Planet->Info.SlotsNum));

	if (!BuildingIconClass) return;
	BuildingTable->ClearChildren();

	for (int32 i = 0; i < 9; i++)
	{
		UNamedSlot* NamedSlot = WidgetTree->ConstructWidget<UNamedSlot>();

		if (NamedSlot)
		{
			BuildingTable->AddChildToUniformGrid(NamedSlot, FMath::Fmod(i, 3), FMath::DivideAndRoundDown(i, 3));
		}
	}

	for (int32 i = 0; i < Planet->Info.SlotsNum; i++)
	{
		UBuildingIconUWB* BuildingIconWidget = WidgetTree->ConstructWidget<UBuildingIconUWB>(BuildingIconClass);

		if (BuildingIconWidget)
		{
			BuildingTable->AddChildToUniformGrid(BuildingIconWidget, FMath::DivideAndRoundDown(i, 3), FMath::Fmod(i, 3));
			//GEngine->AddOnScreenDebugMessage(FText::AsNumber(FMath::DivideAndRoundUp(i, 3)));
			//GEngine->AddOnScreenDebugMessage(FText::AsNumber(FMath::Fmod(i, 3)));
			//BuildingIconWidget->InitializeLevelWidget(HUD, i);
			//Planet->Buildings[i].
			if (i < Planet->Buildings.Num()) {
				BuildingIconWidget->InitializeIconWidget(Planet->Buildings[i].Building, Planet->Buildings[i].Type);
			}
			else BuildingIconWidget->InitializeIconWidget();
			BuildingIconWidgets.Add(BuildingIconWidget);
		}
	}
	/*
	PlanetResourcesDescTextBox->SetText();
	PlanetEffectsDescTextBox->SetText();*/
}
