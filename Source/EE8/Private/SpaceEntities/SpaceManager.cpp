// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/SpaceManager.h"
#include "SpaceEntities/Star.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ASpaceManager::ASpaceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LBComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	LBComponent->DefaultLifeTime = 0.0f;

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

	RStream = FRandomStream(Parameters.Seed);// specify seed
}

void ASpaceManager::InitializeSpace()
{
	for (int32 i = 0; i < SpaceSpawnParameters.NumberOfStars; i++)
	{
		GenerateStarSystem();
	}
	DrawConnectionWithStars();
}

void ASpaceManager::GenerateStarSystem()
{
	FTransform StarTransform= GetCheckedSystemData();
	AStar* Star = Cast<AStar>(GetWorld()->SpawnActor(StarClass, &(StarTransform)));
	
	int32 Seed = FMath::FloorToInt32<double>(RStream.FRandRange(-100.0f, 100.0f));
	Star->Initialize(Seed);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), SystemDat.NearestNeighbours->Num(), 0, 0));
	Stars.Add(Star);
}

FTransform ASpaceManager::GetSystemTransform()
{
	FTransform Transform;
	float Perlin3D;

	do
	{
		Transform.SetLocation(FVector(
			RStream.FRandRange(-1.0f, 1.0f), 
			RStream.FRandRange(-1.0f, 1.0f), 
			RStream.FRandRange(-1.0f, 1.0f)
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

TArray<FVector> ASpaceManager::CheckSystemTransform(FTransform SystemTransform)
{
	TArray<FVector> NearestNeighboursLoc;
	FVector NearestNeighbourLocation = FVector(MAX_FLT, MAX_FLT, MAX_FLT);//init with max float value
	
	for (AStar* Star : Stars)//distance check
	{
		float Distance = (SystemTransform.GetLocation() - Star->GetActorLocation()).Length();

		if (Distance < (SystemTransform.GetLocation() - NearestNeighbourLocation).Length())//update nearest neighbour location
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f = FloatVariable / %s = StringVariable"), Distance, ": star"));
			NearestNeighbourLocation = Star->GetActorLocation();
		}
			
		if (Distance < SpaceSpawnParameters.SystemRadius * 3.0f)//min distance check
		{
			return TArray<FVector>();
		}

		if (Distance < SpaceSpawnParameters.NearestNeighbourRadius)//check and return neighbours in radius WeldDistance
		{
			NearestNeighboursLoc.Add(SystemTransform.GetLocation());
			NearestNeighboursLoc.Add(Star->GetActorLocation());
		}
	}

	if (NearestNeighboursLoc.IsEmpty())//if there`s no neighbours in radius WeldDistance, put the nearest found
		NearestNeighboursLoc.Add(SystemTransform.GetLocation());
		NearestNeighboursLoc.Add(NearestNeighbourLocation);
	/*
		for (int32 i = 0; i < NearestNeighboursLoc.Num(); i++) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), NearestNeighboursLoc[i].X, NearestNeighboursLoc[i].Y, NearestNeighboursLoc[i].Z));
		}
	*/
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), 1.0, 2.0, 3.0));
	return NearestNeighboursLoc;// seems to be not working
}

FTransform ASpaceManager::GetCheckedSystemData()
{
	FTransform Transform;
	TArray<FVector> Neighbours;

	do
	{
		Transform = GetSystemTransform();
		Neighbours = CheckSystemTransform(Transform);
	} while (Neighbours.IsEmpty());

	Connections.Append(Neighbours);

	return Transform;
}

void ASpaceManager::DrawConnectionWithStars()
{
	TArray<FBatchedLine> lines;
	for (int32 i = 1; i < Connections.Num(); i+=2)
	{
		FVector Start = Connections[i-1];
		FVector End = Connections[i];

		FBatchedLine line = FBatchedLine(Start,
			End,
			DrawColor,
			0.0, // for infinity period draw
			0.0,
			4
		);
		lines.Add(line);
	}
	LBComponent->DrawLines(lines);
}