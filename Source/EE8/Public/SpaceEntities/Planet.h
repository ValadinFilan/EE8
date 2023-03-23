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

	UMaterialInterface* CloudsMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CloudSphere;

	//UMaterialInstanceDynamic* CloudsDynamicMaterial;


	//UMaterialInstanceDynamic* SetCloudsMaterial();

public:

	APlanet();

	void Initialize(int32 CosmeticSeed);

	int32 GetCosmeticSeed();

	UFUNCTION(BlueprintCallable)
	bool SetPlanetVisibility(bool Visibility);

};
