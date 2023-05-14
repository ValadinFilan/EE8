// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlanetLineUWB.generated.h"

class UButton;
class UTextBlock;
class APlanet;

/**
 * 
 */
UCLASS()
class EE8_API UPlanetLineUWB : public UUserWidget
{
	GENERATED_BODY()
protected:

	APlanet* TargetPlanet;

public:
	void InitializePlanetLineWidget(APlanet* Planet);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PlanetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Data;
};
