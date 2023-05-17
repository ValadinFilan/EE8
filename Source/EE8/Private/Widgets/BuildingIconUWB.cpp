// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingIconUWB.h"
#include "SpaceHUD.h"
#include "Components/TextWidgetTypes.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"

#include "SpaceEntities/Buildings/ExtractBuilding.h"
#include "SpaceEntities/Buildings/DefenceBuilding.h"
#include "SpaceEntities/Buildings/ManagementBuilding.h"
#include "SpaceEntities/Buildings/ShipyardBuilding.h"

#include "..\..\Public\Widgets\BuildingIconUWB.h"

void UBuildingIconUWB::InitializeIconWidget(UBuilding* BuildingPointer, bool ChangeGameState)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("YYY"));
	Building = BuildingPointer;
	Type = BuildingPointer->GetBuildingType();
	IconButton->OnClicked.AddUniqueDynamic(this, &UBuildingIconUWB::OpenUIBuildingTab);

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
	if (ChangeGameState) OpenUIBuildingTab();
}

void UBuildingIconUWB::InitializeIconWidget()
{
	Building = nullptr;
	IconButton->OnClicked.AddUniqueDynamic(this, &UBuildingIconUWB::OpenUIBuildingTab);
	if (EmptySlotIcon) Image->SetBrushFromTexture(EmptySlotIcon);
}

void UBuildingIconUWB::OpenUIBuildingTab()
{
	if (!Building)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("if"));
		OnButtonClicked.Broadcast(EUIGameStates::CreateBuilding, nullptr, this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("else"));
		OnButtonClicked.Broadcast(EUIGameStates::Building, Building, this);
	}
}
