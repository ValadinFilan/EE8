// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PlanetUWB.generated.h"

class UButton;
class UTextBlock;
class APlanet;
class UBuilding;
class UBuildingIconUWB;

/**
 * 
 */
UCLASS()
class EE8_API UPlanetUWB : public UUserWidget
{
	GENERATED_BODY()

	APlanet* Planet;

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UBuildingIconUWB> BuildingIconClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UUniformGridPanel* BuildingTable;

	TArray<UBuildingIconUWB*> BuildingIconWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetNameMainTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetNameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetPopulationTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetSlotNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetDescTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetResourcesMetalTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetResourcesCarbonTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetEffectsDescTextBox;

	APlanet* GetPlanet();

	void InitializePlanetWidget(APlanet* TargetPlanet);

	UFUNCTION()
	void UnhideBuildingTable();
	void FirstInitializePlanetWidget();
};
