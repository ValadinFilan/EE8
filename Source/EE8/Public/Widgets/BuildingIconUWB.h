// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingIconUWB.generated.h"

class ASpaceHUD;
enum class EUIGameStates : uint8;
class UButton;
class UImage;

class UBuilding;
enum class EBuildingType : uint8;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FBuildingState, EUIGameStates, UBuilding*, UBuildingIconUWB*);

/**
 * 
 */
UCLASS()
class EE8_API UBuildingIconUWB : public UUserWidget
{
	GENERATED_BODY()

private:

	UBuilding* Building;

	EBuildingType Type;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* IconButton;

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

	FBuildingState OnButtonClicked;

	void InitializeIconWidget(UBuilding* BuildingPointer, bool ChangeGameState);

	void InitializeIconWidget();

	void ClearIconWidget();

	UFUNCTION()
	void OpenUIBuildingTab();
};
