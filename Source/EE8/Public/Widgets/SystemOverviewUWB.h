// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SystemOverviewUWB.generated.h"

class AStarPlayerState;
class UButton;
class UTextBlock;
class APlanet;
class UPlanetLineUWB;

/**
 * 
 */
UCLASS()
class EE8_API USystemOverviewUWB : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPlanetLineUWB> PlanetLineWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UPanelWidget* PlanetTable;

	TArray<UPlanetLineUWB*> PlanetLineWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* MetalTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* EnergyTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* CarbonTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* MetalIncomeTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* EnergyIncomeTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* CarbonIncomeTextBox;

	void InitializeSystemOverviewWidget(AStarPlayerState* StarPlayerState);

	UFUNCTION()
	void UpdateMetal(float NewMetal);

	UFUNCTION()
	void UpdateEnergy(float NewEnergy);

	UFUNCTION()
	void UpdateCarbon(float NewCarbon);

	UFUNCTION()
	void UpdateMetalIncome(float Increment);

	UFUNCTION()
	void UpdateEnergyIncome(float Increment);

	UFUNCTION()
	void UpdateCarbonIncome(float Increment);

	UFUNCTION()
	void AddCapturedPlanet(APlanet* Planet);

	void RenewPlanetData(APlanet* Planet);

};
