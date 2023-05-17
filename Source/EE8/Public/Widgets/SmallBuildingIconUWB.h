// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SmallBuildingIconUWB.generated.h"

class UImage;
class UBuilding;


/**
 * 
 */
UCLASS()
class EE8_API USmallBuildingIconUWB : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* TypeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* LevelImage;

	//Type

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* EmptySlotIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ExtractIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ShipyardIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DefenceIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ManagementIcon;

	//Level

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Lv1Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Lv2Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Lv3Icon;

	void InitializeSmallBuildingIconWidget(UBuilding* Building);
};
