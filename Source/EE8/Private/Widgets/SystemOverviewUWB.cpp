// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/SystemOverviewUWB.h"
#include "Player/StarPlayerState.h"
#include "Widgets/PlanetLineUWB.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

void USystemOverviewUWB::InitializeSystemOverviewWidget(AStarPlayerState* StarPlayerState)
{
	MetalTextBox->SetText(FText::AsNumber(StarPlayerState->Metal));
	EnergyTextBox->SetText(FText::AsNumber(StarPlayerState->Energy));
	CarbonTextBox->SetText(FText::AsNumber(StarPlayerState->Carbon));
	MetalIncomeTextBox->SetText(FText::AsNumber(StarPlayerState->MetalIncome));
	EnergyIncomeTextBox->SetText(FText::AsNumber(StarPlayerState->EnergyIncome));
	CarbonIncomeTextBox->SetText(FText::AsNumber(StarPlayerState->CarbonIncome));

	StarPlayerState->OnMetalIncomeUpdate.AddUObject(this, &USystemOverviewUWB::UpdateMetalIncome);
	StarPlayerState->OnEnergyIncomeUpdate.AddUObject(this, &USystemOverviewUWB::UpdateEnergyIncome);
	StarPlayerState->OnCarbonIncomeUpdate.AddUObject(this, &USystemOverviewUWB::UpdateCarbonIncome);
	StarPlayerState->OnMetalUpdate.AddUObject(this, &USystemOverviewUWB::UpdateMetal);
	StarPlayerState->OnEnergyUpdate.AddUObject(this, &USystemOverviewUWB::UpdateEnergy);
	StarPlayerState->OnCarbonUpdate.AddUObject(this, &USystemOverviewUWB::UpdateCarbon);
	StarPlayerState->OnPlanetAdd.AddUObject(this, &USystemOverviewUWB::AddCapturedPlanet);
	StarPlayerState->OnPlanetRenew.AddUObject(this, &USystemOverviewUWB::RenewPlanetData);
}

void USystemOverviewUWB::UpdateMetal(float NewMetal)
{
	MetalTextBox->SetText(FText::AsNumber(NewMetal));
}

void USystemOverviewUWB::UpdateEnergy(float NewEnergy)
{
	EnergyTextBox->SetText(FText::AsNumber(NewEnergy));
}

void USystemOverviewUWB::UpdateCarbon(float NewCarbon)
{
	CarbonTextBox->SetText(FText::AsNumber(NewCarbon));
}

void USystemOverviewUWB::UpdateMetalIncome(float NewMetalIncome)
{
	MetalIncomeTextBox->SetText(FText::AsNumber(NewMetalIncome));
}

void USystemOverviewUWB::UpdateEnergyIncome(float NewEnergyIncome)
{
	EnergyIncomeTextBox->SetText(FText::AsNumber(NewEnergyIncome));
}

void USystemOverviewUWB::UpdateCarbonIncome(float NewCarbonIncome)
{
	CarbonIncomeTextBox->SetText(FText::AsNumber(NewCarbonIncome));
}

void USystemOverviewUWB::AddCapturedPlanet(APlanet* Planet)
{
	if (!PlanetLineWidgetClass) return;
	UPlanetLineUWB* PlanetLineWidget = WidgetTree->ConstructWidget<UPlanetLineUWB>(PlanetLineWidgetClass);
	if (PlanetLineWidget)
	{
		PlanetTable->AddChild(PlanetLineWidget);
		PlanetLineWidget->InitializePlanetLineWidget(Planet);
		PlanetLineWidgets.Add(PlanetLineWidget);
	}
}

void USystemOverviewUWB::RenewPlanetData(APlanet* Planet)
{
	if (!PlanetLineWidgetClass) return;

	for (UPlanetLineUWB* PlanetLineWidget : PlanetLineWidgets)
	{
		if (PlanetLineWidget->TargetPlanet == Planet)
		{
			PlanetLineWidget->InitializePlanetLineWidget(Planet);
		}
	}
}
