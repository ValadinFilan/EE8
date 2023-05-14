// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Building.generated.h"

class APlanet;

UENUM(BlueprintType)
enum class EBuildingType : uint8 
{
	Extract,
	Shipyard,
	Defence,
	Management,
	Empty
};

USTRUCT(BlueprintType)
struct FBuildingLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* LevelImage;

	UPROPERTY(BlueprintReadWrite)
	float LevelBuff;

	UPROPERTY(BlueprintReadWrite)
	FName BuildingName;

};

/**
 * 
 */
UCLASS(Abstract)
class EE8_API UBuilding : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FBuildingLevel> BuildingLevels;

	UPROPERTY(EditDefaultsOnly)
	EBuildingType BuildingType;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	APlanet* OwningPlanet;

	virtual void Initialize(APlanet* Planet);

	virtual void Update();

	virtual void UpgrageLevel();

	UFUNCTION(BlueprintCallable)
	FBuildingLevel GetBuildingLevelData();

	UFUNCTION(BlueprintCallable)
	int32 GetBuildingLevel();

	UFUNCTION(BlueprintCallable)
	EBuildingType GetBuildingType();
};
