// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Star.h"
#include "SpaceEntities/Planet.h"
#include "DrawDebugHelpers.h"

double AStar::RandNormDist(double U1, double U2, double mu, double sigma)
{
	double result = FMath::Sqrt(-2 * log(U1)) * FMath::Cos(2 * PI * U2);
	result = result * sigma + mu;

	return result;
}

AStar::AStar()
{
	LBComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	LBComponent->DefaultLifeTime = 0.0f;

	bReplicates = true;
}

void AStar::Initialize(int32 Seed, TArray<FVector> NearestNeighbours)
{
	Super::Initialize();

	RStream = FRandomStream(Seed);// specify seed
	Neighbours = NearestNeighbours;
	DrawConnectionWithStars();
	SpawnPlanets();
}

void AStar::DrawConnectionWithStars()
{
	TArray<FBatchedLine> lines;
	for (int32 i = 0; i < Neighbours.Num(); i++)
	{
		FVector Start = FVector(Neighbours[i].X, Neighbours[i].Y, Neighbours[i].Z);

		FBatchedLine line = FBatchedLine(Start,
			GetActorLocation(),
			DrawColor,
			0.0, // for infinity period draw
			0.0,
			4
		);
		lines.Add(line);
	}
	LBComponent->DrawLines(lines);
}

void AStar::SpawnPlanets()
{
	const int32 MaxNum = RStream.RandRange(Parameters.MinPlanetNum, Parameters.MaxPlanetNum);
	float Orbit = Parameters.MinDistanceToStar;
	for (int i = 0; i < MaxNum; i++)
	{
		const float SemiMajorAxis = Orbit + RandNormDist(RStream.FRand(), RStream.FRand(), Parameters.MeanPlanetsInterval, 100.0f);
		const float Eccentricity = FMath::Abs(FMath::Min(RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 0.2f), 0.9));
		const float Inclination = RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);
		const float LongitudeofAN = RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);

		Planets.Add(GeneratePlanet(SemiMajorAxis, Eccentricity, Inclination, LongitudeofAN));

		Orbit = SemiMajorAxis;
	}
}

APlanet* AStar::GeneratePlanet(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN)//gen orbit and planet using kepler parameters
{
	const FRotator Rot(FRotator(Inclination, 0, LongitudeofAN) + GetActorRotation()); //orbit personal rotator

	FVector Center = Rot.RotateVector(FVector(Eccentricity * SemiMajorAxis, 0, 0)) + GetActorLocation();//center of orbit - not a star coordinates

	float SemiMinorAxis = sqrt(-pow((Eccentricity * SemiMajorAxis), 2) + pow(SemiMajorAxis, 2));
	FVector X = FVector(0, SemiMinorAxis, 0);
	FVector Y = FVector(SemiMajorAxis, 0, 0);

	X = Rot.RotateVector(X);
	Y = Rot.RotateVector(Y);

	LBComponent->DrawCircle(Center, X, Y, DrawColor.ToFColor(true), 1.0f, 64, 4);
	
	float PlanetRandomSeed = RStream.FRandRange(-PI, PI);// defines planet location along an orbit

	FVector PlanetLocation = Rot.RotateVector(FVector(sin(PlanetRandomSeed) * SemiMajorAxis, cos(PlanetRandomSeed) * SemiMinorAxis, 0)) + Center;
	FTransform PlanetTransform = FTransform(GetActorRotation().Quaternion(), PlanetLocation);

	APlanet* Planet = GetWorld()->SpawnActor<APlanet>(PlanetClass, PlanetTransform);
	//Planet->Initialize(i);

	return Planet;
}

