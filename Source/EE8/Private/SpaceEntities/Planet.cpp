// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Planet.h"

APlanet::APlanet()
{
	bReplicates = true;
}

void APlanet::Initialize(int32 Index)
{
	PrimaryActorTick.bCanEverTick = true;

	CloudSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudSphere"));
	CloudSphere->SetVisibility(true);
	CloudSphere->SetupAttachment(ObjectMesh);
}

void APlanet::Initialize(int32 CosmeticSeed)
{
	RSeed = CosmeticSeed;
	RStream = FRandomStream(RSeed);
	Scale = FVector(RStream.FRandRange(0.1f, 0.5f));//RandNormDist(RStream.FRand(), RStream.FRand(), 0.0f, 0.5f))
	SetActorScale3D(Scale);
	//SetBaseMaterial();
	//SetCloudsMaterial();
	//Material = UMaterialInstance(MaterialClouds);
	//Material = ObjectMesh->OverrideMaterials();
	//ObjectMesh->SetMaterial(0, Material);
	//Material->SetScalarParameterValue(FName(TEXT("CosmeticSeed")), FMath::RandRange(0, 1));
	Super::Initialize();
}

/* //не удалять - это на будущее
UMaterialInstanceDynamic* APlanet::SetCloudsMaterial()
{
	CloudsDynamicMaterial = CloudSphere->CreateDynamicMaterialInstance(0, CloudsMaterial);
	CloudSphere->SetMaterial(0, CloudsDynamicMaterial);
	float Fresnel = RStream.FRandRange(0.25f, 30.0f);
	float Min_faloff = -0.6434767 + (1.6356916) / (1 + FMath::Pow((Fresnel / 8.007612), 0.8310156));
	CloudsDynamicMaterial->SetScalarParameterValue(FName(TEXT("Fresnel_density")), Fresnel);
	CloudsDynamicMaterial->SetScalarParameterValue(FName(TEXT("Atmosphere_falloff")), RStream.FRandRange(Min_faloff, 1.0f));
	CloudsDynamicMaterial->SetScalarParameterValue(FName(TEXT("Speed")), RStream.FRandRange(0.0f, Scale.X*2));
	return CloudsDynamicMaterial;
}
*/

int32 APlanet::GetCosmeticSeed()
{
	return RSeed;
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
