// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/SpaceManager.h"
#include "SpaceEntities/Star.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

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
	for (AStar* Star : Stars)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), Star->GetActorLocation().X, Star->GetActorLocation().Y, Star->GetActorLocation().Z));
	}
}

// Called every frame
void ASpaceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceManager::SetSpawningParameters(FSpaceSpawnParameters Parameters)
{
	SpaceSpawnParameters = Parameters;

	RStream = FRandomStream(Parameters.Seed);// specify seed
}

void ASpaceManager::InitializeSpace()
{
	for (int32 i = 0; i < SpaceSpawnParameters.NumberOfStars; i++)
	{
		GenerateStarSystem();
	}

}

void ASpaceManager::GenerateStarSystem()
{
	SystemData SystemDat = GetCheckedSystemData();

	AStar* Star = Cast<AStar>(GetWorld()->SpawnActor(StarClass, &(SystemDat.Transform)));
	
	int32 PlanetCount = FMath::FloorToInt32<double>(FMath::RandRange(SpaceSpawnParameters.MinPlanets, SpaceSpawnParameters.MaxPlanets));
	Star->Initialize(PlanetCount, *(SystemDat.NearestNeighbours));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), SystemDat.NearestNeighbours->Num(), 0, 0));
	Stars.Add(Star);
	/*
	for (int32 i = 0; i < PlanetCount; i++)
	{
		FTransform PlanetTransform = GetPlanetTransform(Star, i);
		APlanet* Planet = Cast<APlanet>(GetWorld()->SpawnActor(PlanetClass, &PlanetTransform));
		Planet->Initialize(i);
		Planets.Add(Planet);
	}*/
}

FTransform ASpaceManager::GetSystemTransform()
{
	FTransform Transform;
	float Perlin3D;

	do
	{
		Transform.SetLocation(FVector(RStream.FRandRange(-1.0f, 1.0f), RStream.FRandRange(-1.0f, 1.0f), RStream.FRandRange(-1.0f, 1.0f)
			//FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f),
			//FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f),
			//FMath::FRandRange(-SpaceSpawnParameters.GalaxyRadius / 2.0f, SpaceSpawnParameters.GalaxyRadius / 2.0f)
		));

		Transform.SetRotation(FRotator(
			RStream.FRandRange(0.0f, 180.0f),
			RStream.FRandRange(0.0f, 180.0f),
			0
		).Quaternion());
		Perlin3D = FMath::PerlinNoise3D(Transform.GetLocation());
	} while (RStream.FRand() < Perlin3D);//probability check

	Transform.SetLocation(Transform.GetLocation() * SpaceSpawnParameters.GalaxyRadius);//scale Location

	return Transform;
}
/*
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
*/
TArray<FVector>* ASpaceManager::CheckSystemTransform(FTransform SystemTransform)
{
	TArray<FVector> NearestNeighboursLoc;
	FVector NearestNeighbourLocation = FVector(2000000.0f, 2000000.0f, 2000000.0f);//init with max float value
	
	for (AStar* Star : Stars)//distance check
	{
		float Distance = (SystemTransform.GetLocation() - Star->GetActorLocation()).Length();

		if (Distance < (SystemTransform.GetLocation() - NearestNeighbourLocation).Length())//update nearest neighbour location
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f = FloatVariable / %s = StringVariable"), Distance, ": star"));
			NearestNeighbourLocation = Star->GetActorLocation();
		}
			
		if (Distance < SpaceSpawnParameters.SystemRadius * 3.0f)//min distance check
		{
			return nullptr;
		}

		if (Distance < 40000.0)//check and return neighbours in radius WeldDistance
		{
			NearestNeighboursLoc.Add(Star->GetActorLocation());
		}
	}

	if (NearestNeighboursLoc.IsEmpty())//if there`s no neighbours in radius WeldDistance, put the nearest found 
		NearestNeighboursLoc.Add(NearestNeighbourLocation);
	for (auto i = 0; i < NearestNeighboursLoc.Num(); i++) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), NearestNeighboursLoc[i].X, NearestNeighboursLoc[i].Y, NearestNeighboursLoc[i].Z));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), 1.0, 2.0, 3.0));
	return &NearestNeighboursLoc;// seems to be not working
}

SystemData ASpaceManager::GetCheckedSystemData()
{
	FTransform Transform = GetSystemTransform();

	TArray<FVector>* Neighbours = CheckSystemTransform(Transform);

	while (Neighbours == nullptr)//while nullptr
	{
		Transform = GetSystemTransform();

		Neighbours = CheckSystemTransform(Transform);// not ready yet
	}

	SystemData Data = SystemData(Transform, Neighbours);
	//Data.Transform = Transform;
	//Data.NearestNeighbours = Neighbours;

	return Data;
}