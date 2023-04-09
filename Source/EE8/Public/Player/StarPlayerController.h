// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StarPlayerController.generated.h"

class ASpaceObject;
class AShip;
class APlanet;

/**
 * 
 */
UCLASS()
class EE8_API AStarPlayerController : public APlayerController
{
	GENERATED_BODY()

	AStarPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public: 
	virtual void Tick(float DeltaSeconds);

	TWeakObjectPtr<ASpaceObject> CurrentSpaceObject;

	TWeakObjectPtr<AShip> CurrentShip;
	TWeakObjectPtr<APlanet> CurrentPlanet;

	UFUNCTION(BlueprintCallable)
	void GetPlanetView();

	UFUNCTION(BlueprintCallable)
	void SendShipToPlanet();

	UFUNCTION(BlueprintCallable)
	void GetFreeShip();

	UFUNCTION(BlueprintCallable)
	void GetFreePlanet();

	UFUNCTION(BlueprintCallable)
	void DisolveSpaceSnapping();

protected:

	void SnapToSpaceObject(ASpaceObject* SpaceObject);

	ASpaceObject* TraceSpaceObject();
};
