// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingIconUWB.generated.h"

class ASpaceHUD;
class UButton;

/**
 * 
 */
UCLASS()
class EE8_API UBuildingIconUWB : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* IconButton;

	void InitializeIconWidget(ASpaceHUD* HUD);
};
