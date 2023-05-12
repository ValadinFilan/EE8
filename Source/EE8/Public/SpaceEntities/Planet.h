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
	//FPlanetInfo(){}

	/*FPlanetInfo(FString l_Name,
		int32 l_Population,
		FString l_Type,
		FString l_Description,
		float l_EnergyIncome,
		float l_MetalIncome,
		float l_CarbonIncome)
	{
		Name = l_Name;
		Population = l_Population;
		Type = l_Type;
		Description = l_Description;
		EnergyIncome = l_EnergyIncome;
		MetalIncome = l_MetalIncome;
		CarbonIncome = l_CarbonIncome;
	}*/
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Population;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ShortDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnergyIncome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MetalIncome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CarbonIncome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SlotsNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MetalRemaining;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CarbonRemaining;
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
	FPlanetInfo Info;

	void Initialize(int32 CosmeticSeed);

	int32 GetCosmeticSeed();

	UFUNCTION(BlueprintCallable)
	bool SetPlanetVisibility(bool Visibility);

};
