// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Star.h"
#include "SpaceEntities/Planet.h"
#include "DrawDebugHelpers.h"


AStar::AStar()
{
	LBComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	LBComponent->DefaultLifeTime = 0.0f;

	bReplicates = true;
}

void AStar::Initialize(int32 Seed)
{
	RSeed = Seed;
	RStream = FRandomStream(Seed);// specify seed
	Scale = FVector(RStream.FRandRange(1.0f, 10.0f));//RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 0.5f))
	SetActorScale3D(Scale);
	SpawnPlanets();

	Super::Initialize();
}

void AStar::SpawnPlanets()
{
	const int32 MaxNum = RStream.RandRange(Parameters.MinPlanetNum, Parameters.MaxPlanetNum);
	float Orbit = Parameters.MinDistanceToStar + (Scale.X / 2.0f) * 100;
	for (int i = 0; i < MaxNum; i++)
	{
		const float SemiMajorAxis = Orbit + RandNormDist(RStream.FRand(), RStream.FRand(), Parameters.MeanPlanetsInterval, 100.0f);
		const float Eccentricity = FMath::Abs(FMath::Min(RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 0.2f), 0.9));
		const float Inclination = RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);
		const float LongitudeofAN = RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 5.0f);
		const float TrueAnomaly = RStream.FRandRange(-PI, PI);

		Orbits.Add(FOrbitParameters(SemiMajorAxis, Eccentricity, Inclination, LongitudeofAN, TrueAnomaly));
		FTransform PlanetTransform = GeneratePlanetTransform(SemiMajorAxis, Eccentricity, Inclination, LongitudeofAN, TrueAnomaly);
		APlanet* Planet = GetWorld()->SpawnActor<APlanet>(PlanetClass, PlanetTransform);
		Planet->Initialize(RStream.RandRange(-100, 100));
		Planets.Add(Planet);

		Orbit = SemiMajorAxis;
	}
}

bool AStar::GetPlanetsVisibility()
{
	return PlanetsVisibility;
}

void AStar::SetPlanetsVisibility(bool Visibility)
{
	if (Visibility)
	{
		for (int32 i = 0; i != Planets.Num(); i++) {
			Planets[i]->SetPlanetVisibility(false);
			GeneratePlanetTransform(Orbits[i].SemiMajorAxis, Orbits[i].Eccentricity, Orbits[i].Inclination, Orbits[i].LongitudeofAN, Orbits[i].TrueAnomaly);
		}
	}
	else
	{
		for (int32 i = 0; i != Planets.Num(); i++) {
			Planets[i]->SetPlanetVisibility(false);
		}
		LBComponent->Flush();
		PlanetsVisibility = false;
	}
}

FTransform AStar::GeneratePlanetTransform(float SemiMajorAxis, float Eccentricity, float Inclination, float LongitudeofAN, float TrueAnomaly)//gen orbit and planet using kepler parameters
{
	const FRotator Rot(FRotator(Inclination, 0, LongitudeofAN) + GetActorRotation()); //orbit personal rotator

	FVector Center = Rot.RotateVector(FVector(Eccentricity * SemiMajorAxis, 0, 0)) + GetActorLocation();//center of orbit - not a star coordinates

	float SemiMinorAxis = sqrt(-pow((Eccentricity * SemiMajorAxis), 2) + pow(SemiMajorAxis, 2));
	FVector X = FVector(0, SemiMinorAxis, 0);
	FVector Y = FVector(SemiMajorAxis, 0, 0);

	X = Rot.RotateVector(X);
	Y = Rot.RotateVector(Y);
	LBComponent->DrawCircle(Center, X, Y, DrawColor.ToFColor(true), 1.0f, 256, 1);//можно переписать LineBatcher и сделать чтоб оно было нужной толщины!!!!

	FVector PlanetLocation = Rot.RotateVector(FVector(sin(TrueAnomaly) * SemiMajorAxis, cos(TrueAnomaly) * SemiMinorAxis, 0)) + Center;
	FTransform PlanetTransform = FTransform(GetActorRotation().Quaternion(), PlanetLocation);
	//Planet->Initialize(i);

	return PlanetTransform;
}

void AStar::CreateCosmetic_Implementation()
{
	BaseDynamicMaterial = ObjectMesh->CreateDynamicMaterialInstance(0, BaseMaterial);
	ObjectMesh->SetMaterial(0, BaseDynamicMaterial);
	BaseDynamicMaterial->SetScalarParameterValue(FName(TEXT("Temperature")), RStream.FRand());
	BaseDynamicMaterial->SetScalarParameterValue(FName(TEXT("Luminosity")), 30.0);
	//BaseDynamicMaterial->GetParameters
}