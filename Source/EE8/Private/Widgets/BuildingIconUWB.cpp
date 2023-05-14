// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingIconUWB.h"
#include "Components/TextWidgetTypes.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"

#include "SpaceEntities/Buildings/ExtractBuilding.h"
#include "SpaceEntities/Buildings/DefenceBuilding.h"
#include "SpaceEntities/Buildings/ManagementBuilding.h"
#include "SpaceEntities/Buildings/ShipyardBuilding.h"

#include "..\..\Public\Widgets\BuildingIconUWB.h"

void UBuildingIconUWB::InitializeIconWidget(UBuilding* BuildingPointer, EBuildingType Type)
{
	switch (Type)
	{
	case EBuildingType::Extract:
	{
		if(ExtractIcon) Image->SetBrushFromTexture(ExtractIcon);
		break;
	}
	case EBuildingType::Shipyard:
	{
		if (ShipyardIcon) Image->SetBrushFromTexture(ShipyardIcon);
		break;
	}
	case EBuildingType::Defence:
	{
		if (DefenceIcon) Image->SetBrushFromTexture(DefenceIcon);
		break;
	}
	case EBuildingType::Management:
	{
		if (ManagementIcon) Image->SetBrushFromTexture(ManagementIcon);
		break;
	}
	default:
		if (EmptySlotIcon) Image->SetBrushFromTexture(EmptySlotIcon);
		break;
	}
}

void UBuildingIconUWB::InitializeIconWidget()
{
	if (EmptySlotIcon) Image->SetBrushFromTexture(EmptySlotIcon);
}
