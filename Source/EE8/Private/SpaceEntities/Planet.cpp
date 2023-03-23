// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Planet.h"

APlanet::APlanet()
{
	bReplicates = true;
}

void APlanet::Initialize(int32 Index)
{
	Super::Initialize();

	NumInSystem = Index;
}

int32 APlanet::GetNumInSystem()
{
	return NumInSystem;
}
