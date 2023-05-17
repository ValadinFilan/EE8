// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlanetLineUWB.generated.h"

class UButton;
class UTextBlock;
class APlanet;
class USmallBuildingIconUWB;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class EE8_API UPlanetLineUWB : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializePlanetLineWidget(APlanet* Planet);

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<USmallBuildingIconUWB> SmallBuildingIconClass;

	APlanet* TargetPlanet;

	TArray<USmallBuildingIconUWB*> SmallBuildingIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UHorizontalBox* BuildingTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Data;
};
