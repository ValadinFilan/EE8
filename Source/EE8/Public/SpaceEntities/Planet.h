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

	//FPlanetInfo(){}

	FPlanetInfo(FString l_Name,
		int32 l_Population,
		FString l_Type,
		FString l_Description,
		float l_EnergyIncome,
		float l_MetalIncome,
		float l_CarbonIncome)
	{
		Name = l_Name;
		Population = l_Population;
		Type = l_Type = l_Description;
		Description = l_Description;
		EnergyIncome = l_EnergyIncome;
		MetalIncome = l_MetalIncome;
		CarbonIncome = l_CarbonIncome;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Population;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EnergyIncome;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MetalIncome;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CarbonIncome;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlanetInfo Info = FPlanetInfo(FString("Emanon"),
			1000,
			FString("Terrestrial"),
			FString("Blah-blah-blah..."),
			1.0,
			1.0,
			1.0);

	void Initialize(int32 CosmeticSeed);

	int32 GetCosmeticSeed();

	UFUNCTION(BlueprintCallable)
	bool SetPlanetVisibility(bool Visibility);

};
