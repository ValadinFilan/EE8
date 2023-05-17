// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUWB.generated.h"

class UButton;
class UBuilding;
class APlanet;
class UTextBlock;

/**
 * 
 */
UCLASS()
class EE8_API UBuildingUWB : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* UpgradeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BuildingNameMainTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BuildingNameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BuildingLevelTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BuildingShortDescTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BuildingDescriptionTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* UpgradeCostTextBox;

	UBuilding* Building;

	void InitializeBuildingWidget();

	void InitializeBuildingWidget(UBuilding* TargetBuilding);

	UFUNCTION()
	void BuildingWidgetUpgrade();
};
