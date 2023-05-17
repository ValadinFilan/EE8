// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceEntities/SpaceObject.h"
#include "Planet.generated.h"

class AStarPlayerState;
class UBuilding;
enum class EBuildingType : uint8;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FBuildingCreate, UBuilding* BuildingPointer, EBuildingType BuildingType, bool ChangeGameState);

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlanetInfo
{
	//FPlanetInfo(){}

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

	AStarPlayerState* OwningPlayerState;

public:

	APlanet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlanetInfo Info;

	void Initialize(int32 CosmeticSeed);

	int32 GetCosmeticSeed();

	UFUNCTION(BlueprintCallable)
	bool SetPlanetVisibility(bool Visibility);

	void SetOwningPlayer(AStarPlayerState* PlayerState);

	AStarPlayerState* GetOwningPlayer();

	TArray<UBuilding*> Buildings;

	FBuildingCreate OnCreateBuilding;

	UFUNCTION()
	UBuilding* CreateBuilding(EBuildingType Type);

	UFUNCTION()
	UBuilding* UpgradeBuilding(UBuilding* Building);
};
