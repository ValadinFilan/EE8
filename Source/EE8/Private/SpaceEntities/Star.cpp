// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Star.h"
#include "SpaceEntities/Planet.h"

AStar::AStar()
{
	LBComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	//RStream = FRandomStream(Parameters.Seed);// specify seed
}

void AStar::Initialize(int32 Seed, TArray<FVector> NearestNeighbours)
{
	Super::Initialize();

	DrawColor = FLinearColor(1, 1, 1, 0.98).ToFColor(true);
	RStream = FRandomStream(Seed);// specify seed
	NormGen = NormDistrGenerator();
	Neighbours = NearestNeighbours;
	DrawL();
	SpawnPlanets();
}

void AStar::DrawL()
{
	TArray<FBatchedLine> lines;
	for (auto i = 0; i < Neighbours.Num(); i++)
	{
		FVector start = FVector(Neighbours[i].X, Neighbours[i].Y, Neighbours[i].Z);

		FBatchedLine line = FBatchedLine(start,
			this->GetActorLocation(),
			FLinearColor(1, 1, 1, 0.05),
			0.0, // for infinity period draw
			2.0,
			4
		);
		lines.Add(line);
	}
	LBComponent->DrawLines(lines);
	//
}

void AStar::SpawnPlanets()
{
	int32 MaxNum = RStream.RandRange(Parameters.MinPlanetNum, Parameters.MaxPlanetNum);
	float Orbit = 500.0f;
	for (int i = 0; i < MaxNum; i++)
	{
		float SemiMajorAxis = Orbit + NormGen.RandNormFromUniform(RStream.FRand(), RStream.FRand(), Parameters.MeanPlanetsInterval, 100.0f);
		float Eccentricity = fabs(fmin(NormGen.RandNormFromUniform(RStream.FRand(), RStream.FRand(), 0.0f, 0.2f), 0.9));
		float Inclination = NormGen.RandNormFromUniform(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);
		float LongitudeofAN = NormGen.RandNormFromUniform(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);
		Planets.Add(GeneratePlanet(SemiMajorAxis, Eccentricity, Inclination, LongitudeofAN));
		Orbit = SemiMajorAxis;
	}
}

APlanet* AStar::GeneratePlanet(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN)//gen orbit and planet using kepler parameters
{
	/// <summary>
	/// generate orbit and planet using kepler parameters
	/// </summary>
	/// <param name="SemiMajorAxis">[0, inf]</param>
	/// <param name="Eccentricity">[0,1)</param>
	/// <param name="Inclination">[-360, 360]</param>
	/// <param name="LongitudeofAN">[-360, 360]</param>
	/// <returns>pointer to a planet</returns>

	const FRotator rot(FRotator(Inclination, 0, LongitudeofAN) + this->GetActorRotation()); //orbit personal rotator

	FVector Center = rot.RotateVector(FVector(Eccentricity * SemiMajorAxis, 0, 0)) + this->GetActorLocation();//center of orbit - not a star coordinates

	float SemiMinorAxis = sqrt(-pow((Eccentricity * SemiMajorAxis), 2) + pow(SemiMajorAxis, 2));
	FVector X = FVector(0, SemiMinorAxis, 0);
	FVector Y = FVector(SemiMajorAxis, 0, 0);

	X = rot.RotateVector(X);
	Y = rot.RotateVector(Y);

	DrawCircle(GetWorld(), Center, X, Y, DrawColor, 1.0f, 64, false, 18446744.0f, 4, 2.0f);// draw an orbit

	/// <summary>
	/// gen Planet Transform, create a Planet
	/// </summary>

	float PlanetRandomSeed = RStream.FRandRange(-3.141592, 3.141592);// defines planet location along an orbit

	FVector PlanetLocation = rot.RotateVector(FVector(sin(PlanetRandomSeed) * SemiMajorAxis, cos(PlanetRandomSeed) * SemiMinorAxis, 0)) + Center;
	FTransform PlanetTransform = FTransform(this->GetActorRotation().Quaternion(), PlanetLocation);

	APlanet* Planet = Cast<APlanet>(GetWorld()->SpawnActor(PlanetClass, &PlanetTransform));
	//Planet->Initialize(i);

	//LBComponent->DrawCircle(Center, Center + FVector(10, 10, 10), Center - FVector(10, 10, 10), FColor(1, 1, 0, 0.5), 3.0, 32, 4); // has no lifetime but it`s not working
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), PlanetLocation.X, Center.X, 0));
	return Planet;
}

