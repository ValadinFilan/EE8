// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/SpaceManager.h"
#include "SpaceEntities/Star.h"
#include "SpaceEntities/Planet.h"

// Sets default values
ASpaceManager::ASpaceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpaceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceManager::SetSpawningParameters(FSpaceSpawnParameters Parameters)
{
	SpaceSpawnParameters = Parameters;

	FMath::RandInit(Parameters.Seed);
}

void ASpaceManager::InitializeSpace()
{
	for (int32 i = 0; i < SpaceSpawnParameters.CountOfStars; i++)
	{
		GenerateStarSystem();
	}

}

void ASpaceManager::GenerateStarSystem()
{
	FTransform SystemTransform = GetCheckedSystemTransform();

	AStar* Star = Cast<AStar>(GetWorld()->SpawnActor(StarClass, &SystemTransform));
	
	int32 PlanetCount = FMath::FloorToInt32<double>(FMath::RandRange(SpaceSpawnParameters.MinPlanets, SpaceSpawnParameters.MaxPlanets));
	Star->Initialize(PlanetCount);
	Stars.Add(Star);

	for (int32 i = 0; i < PlanetCount; i++)
	{
		FTransform PlanetTransform = GetPlanetTransform(Star, i);
		APlanet* Planet = Cast<APlanet>(GetWorld()->SpawnActor(PlanetClass, &PlanetTransform));
		Planet->Initialize(i);
		Planets.Add(Planet);
	}
}

FTransform ASpaceManager::GetSystemTransform()
{
	FTransform Transform;

	Transform.SetLocation(FVector(
		FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f),
		FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f),
		FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f)
	));

	Transform.SetRotation(FRotator(
		FMath::FRandRange(0.0f, 180.0f),
		FMath::FRandRange(0.0f, 180.0f),
		0
	).Quaternion());

	return Transform;
}

FTransform ASpaceManager::GetPlanetTransform(AStar* System, int32 Index)
{
	if (!System) return FTransform();

	float PlanetRadius = (Index + 1) * SpaceSpawnParameters.SystemRadius / System->GetCountOfPlanets();

	FVector SystemX = System->GetActorRotation().Quaternion().GetForwardVector();
	FVector SystemY = System->GetActorRotation().Quaternion().GetRightVector();

	float X = FMath::RandRange(-PlanetRadius, PlanetRadius);

	float Y = (FMath::RandBool() ? (1.0f) : (-1.0f)) * FMath::Sqrt(PlanetRadius * PlanetRadius - X * X);

	FTransform Transfrom;
	Transfrom.SetLocation(System->GetActorLocation() + X * SystemX + Y * SystemY);
	Transfrom.SetRotation(System->GetActorRotation().Quaternion());

	return Transfrom;
}

bool ASpaceManager::CheckSystemTransform(FTransform SystemTransform)
{
	for (AStar* Star : Stars)
	{
		if ((SystemTransform.GetLocation() - Star->GetActorLocation()).Length() < SpaceSpawnParameters.SystemRadius * 3.0f)
		{
			return false;
		}
	}

	return true;
}

FTransform ASpaceManager::GetCheckedSystemTransform()
{
	FTransform Transform = GetSystemTransform();

	while (!CheckSystemTransform(Transform))
	{
		Transform = GetSystemTransform();
	}

	return Transform;
}

