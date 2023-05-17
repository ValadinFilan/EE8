// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/Buildings/Building.h"
#include "ExtractBuilding.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API UExtractBuilding : public UBuilding
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly)
	float BaseProduction = 10.f;

	virtual void Update() override;

	virtual void Initialize(APlanet* Planet) override;
};
