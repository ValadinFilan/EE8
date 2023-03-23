// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceEntities/Ship.h"
#include "StarPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EE8_API AStarPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShip> SpawningShipClass;

	TArray<AShip*> PlayerShips;

	virtual void BeginPlay() override;

};
