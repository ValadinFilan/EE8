// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Star.h"

void AStar::Initialize(int32 PlanetCount)
{
	Super::Initialize();

	CountOfPlanets = PlanetCount;
}

int32 AStar::GetCountOfPlanets()
{
	return CountOfPlanets;
}
