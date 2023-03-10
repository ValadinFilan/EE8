// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Planet.h"

void APlanet::Initialize(int32 Index)
{
	Super::Initialize();

	NumInSystem = Index;
}

int32 APlanet::GetNumInSystem()
{
	return NumInSystem;
}

bool APlanet::SetPlanetVisibility(bool Visibility)
{
	TArray<UStaticMeshComponent*> Meshes;
	GetComponents(Meshes);
	for (UStaticMeshComponent*& M : Meshes)
	{
		M->SetVisibility(Visibility, true);
	}
	SetActorEnableCollision(Visibility);
	SetActorTickEnabled(Visibility);
	return false;
}
