// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SmallBuildingIconUWB.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "SpaceEntities/Buildings/Building.h"
#include "..\..\Public\Widgets\SmallBuildingIconUWB.h"

void USmallBuildingIconUWB::InitializeSmallBuildingIconWidget(UBuilding* Building)
{
	switch (Building->GetBuildingType())
		{
		case EBuildingType::Extract:
		{
			if (ExtractIcon) TypeImage->SetBrushFromTexture(ExtractIcon);
			break;
		}
		case EBuildingType::Shipyard:
		{
			if (ShipyardIcon) TypeImage->SetBrushFromTexture(ShipyardIcon);
			break;
		}
		case EBuildingType::Defence:
		{
			if (DefenceIcon) TypeImage->SetBrushFromTexture(DefenceIcon);
			break;
		}
		case EBuildingType::Management:
		{
			if (ManagementIcon) TypeImage->SetBrushFromTexture(ManagementIcon);
			break;
		}
		default:
			if (EmptySlotIcon) TypeImage->SetBrushFromTexture(EmptySlotIcon);
			break;
		}

	switch (Building->GetBuildingLevel())
	{
	case 1:
	{
		if (ExtractIcon) LevelImage->SetBrushFromTexture(Lv1Icon);
		break;
	}
	case 2:
	{
		if (ShipyardIcon) LevelImage->SetBrushFromTexture(Lv2Icon);
		break;
	}
	case 3:
	{
		if (DefenceIcon) LevelImage->SetBrushFromTexture(Lv3Icon);
		break;
	}
	default:
		if (EmptySlotIcon) LevelImage->SetBrushFromTexture(EmptySlotIcon);
		break;
	}
}
