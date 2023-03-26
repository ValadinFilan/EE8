// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlanetUWB.generated.h"

class ASpaceHUD;
class UButton;
class UTextLayoutWidget;

/**
 * 
 */
UCLASS()
class EE8_API UPlanetUWB : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* HideButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetNameMainTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetNameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetTypeTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetDescTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetResourcesTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetResourcesDescTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetEffectsTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* PlanetEffectsDescTextBox;

	void InitializePlanetWidget(ASpaceHUD* HUD);
};
