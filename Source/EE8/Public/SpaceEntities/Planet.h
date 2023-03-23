// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Planet.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API APlanet : public ASpaceObject
{
	GENERATED_BODY()

protected:

	APlanet();

	UPROPERTY()
	int32 NumInSystem;

public:

	void Initialize(int32 Index);

	int32 GetNumInSystem();

};
