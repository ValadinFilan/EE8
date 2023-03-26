// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Planet.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlanetInfo
{
	GENERATED_BODY()

public:

	FPlanetInfo() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name = FString("Emanon");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Population = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Type = FString("Terrestrial");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Description = FString("Blah-blah-blah...");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EnergyIncome = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MetalIncome = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CarbonIncome = 0.f;
};

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

	UPROPERTY(EditAnywhere)
	FPlanetInfo Info;

	void Initialize(int32 CosmeticSeed);

	int32 GetCosmeticSeed();

	UFUNCTION(BlueprintCallable)
	bool SetPlanetVisibility(bool Visibility);

};
