// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/Buildings/Building.h"
#include "DefenceBuilding.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API UDefenceBuilding : public UBuilding
{
	GENERATED_BODY()
public:
	virtual void Initialize(APlanet* Planet) override;
};
