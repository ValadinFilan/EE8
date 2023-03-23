// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StarPlayerState.h"

void AStarPlayerState::BeginPlay()
{
	AShip* Ship = GetWorld()->SpawnActor<AShip>(SpawningShipClass);
	PlayerShips.Add(Ship);
}
