// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "SpaceHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUIChangeState, EUIGameStates);

/*Enum for states of UI*/
UENUM(BlueprintType)
enum class EUIGameStates : uint8 {
	MainMenu,
	Planet,
	Building,
	Spaceship,
	SystemOverview
};
/**
 * 
 */

UCLASS()
class EE8_API ASpaceHUD : public AHUD
{
	GENERATED_BODY()

public:

	EUIGameStates CurentUIGameState = EUIGameStates::Planet;

	UPROPERTY(VisibleAnywhere)
	TMap<EUIGameStates, UUserWidget*> GameWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EUIGameStates, TSubclassOf<UUserWidget>> GameWidgetClasses;

	virtual void BeginPlay();

	void Initialize();

	void SetUIState(EUIGameStates UIState);

	UFUNCTION()
	void HideCurrentWidget();
};
