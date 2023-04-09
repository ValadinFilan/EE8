// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlanetUWB.h"
#include "Widgets/BuildingIconUWB.h"
#include "Components/TextBlock.h"
#include "SpaceEntities/Planet.h"
//#include "Components/RichTextBlock.h"

#include "Components/Button.h"

void UPlanetUWB::InitializePlanetWidget(APlanet* Planet)
{
	PlanetNameMainTextBox->SetText(FText::FromString(Planet->Info.Name));
	PlanetDescTextBox->SetText(FText::FromString(Planet->Info.Description));
	/*PlanetNameTextBox->SetText();
	PlanetTypeTextBox->SetText();
	PlanetDescTextBox->SetText();
	PlanetResourcesDescTextBox->SetText();
	PlanetEffectsDescTextBox->SetText();*/
}
