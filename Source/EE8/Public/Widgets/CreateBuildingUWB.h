// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateBuildingUWB.generated.h"


class APlanet;
class UButton;
class UTextBlock;
class AStarPlayerState;
//enum class EBuildingType : uint8;

class UBuildingIconUWB;

/**
 * 
 */
UCLASS()
class EE8_API UCreateBuildingUWB : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* BExtractButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* BShipyardButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* BDefenceButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* BManagementButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Metal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Carbon;

	APlanet* Planet;

	UBuildingIconUWB* BuildingIconWidget;

	void InitializeCreateBuildingWidget(APlanet* TargetPlanet, UBuildingIconUWB* TargetBuildingIconWidget);

	UFUNCTION()
		void CreateExtractBuilding();

	UFUNCTION()
		void CreateShipyardBuilding();

	UFUNCTION()
		void CreateDefenceBuilding();

	UFUNCTION()
		void CreateManagementBuilding();

	UFUNCTION()
		void UpdateMetal(float NewMetal);

	UFUNCTION()
		void UpdateEnergy(float NewEnergy);

	UFUNCTION()
		void UpdateCarbon(float NewCarbon);
};
