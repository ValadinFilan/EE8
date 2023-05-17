// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateBuildingUWB.generated.h"


class APlanet;
class UButton;
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
};
