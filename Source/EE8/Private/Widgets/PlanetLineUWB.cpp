// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlanetLineUWB.h"
#include "SpaceEntities/Planet.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UPlanetLineUWB::InitializePlanetLineWidget(APlanet* Planet)
{
	TargetPlanet = Planet;
	PlanetName->SetText(FText::FromString(Planet->Info.Name));
}