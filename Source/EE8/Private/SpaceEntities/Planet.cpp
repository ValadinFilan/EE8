// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Planet.h"
#include "SpaceEntities/Buildings/ExtractBuilding.h"
#include "SpaceEntities/Buildings/DefenceBuilding.h"
#include "SpaceEntities/Buildings/ManagementBuilding.h"
#include "SpaceEntities/Buildings/ShipyardBuilding.h"
#include "Player/StarPlayerState.h"
#include "..\..\Public\SpaceEntities\Planet.h"

APlanet::APlanet()
{
	bReplicates = true;
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
	Info.Population = RStream.RandRange(10000, MAX_int32);
	Info.EnergyIncome = RStream.FRandRange(1.f, 100.f);//delete
	Info.MetalIncome = RStream.FRandRange(1.f, 100.f);//delete
	Info.CarbonIncome = RStream.FRandRange(1.f, 100.f);//delete
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

void APlanet::SetOwningPlayer(AStarPlayerState* PlayerState)
{
	OwningPlayerState = PlayerState;
}

AStarPlayerState* APlanet::GetOwningPlayer()
{
	return OwningPlayerState;
}

UBuilding* APlanet::CreateBuilding(EBuildingType Type)
{
	UBuilding* NewBuilding;
	if (Info.SlotsNum < Buildings.Num()) return nullptr;
	switch (Type)
	{
	case EBuildingType::Extract:
		{
		if ((OwningPlayerState->Metal < 300)||(Buildings.Num() == 0)) return nullptr;//UExtractBuilding cost
		OwningPlayerState->Metal -= 300;
		UExtractBuilding* NewExtractBuilding;
		NewExtractBuilding = NewObject<UExtractBuilding>();
		NewExtractBuilding->Initialize(this);
		OwningPlayerState->AddMetalIncome(NewExtractBuilding->BaseProduction);
		NewBuilding = Cast<UBuilding>(NewExtractBuilding);
		break;
		}
	case EBuildingType::Shipyard:
		{
		if ((OwningPlayerState->Metal < 300) || (Buildings.Num() == 0)) return nullptr;//UShipyardBuilding cost
		OwningPlayerState->Metal -= 300;
		UShipyardBuilding* NewShipyardBuilding;
		NewShipyardBuilding = NewObject<UShipyardBuilding>();
		NewShipyardBuilding->Initialize(this);
		NewBuilding = Cast<UBuilding>(NewShipyardBuilding);
		break;
		}
	case EBuildingType::Defence:
		{
		if ((OwningPlayerState->Metal < 300) || (Buildings.Num() == 0)) return nullptr;//UDefenceBuilding cost
		OwningPlayerState->Metal -= 300;
		UDefenceBuilding* NewDefenceBuilding;
		NewDefenceBuilding = NewObject<UDefenceBuilding>();
		NewDefenceBuilding->Initialize(this);
		NewBuilding = Cast<UBuilding>(NewDefenceBuilding);
		break;
		}
	case EBuildingType::Management:
		{
		if (OwningPlayerState->Metal < 300) return nullptr;//UManagementBuilding cost
		OwningPlayerState->Metal -= 300;
		UManagementBuilding* NewManagementBuilding;
		NewManagementBuilding = NewObject<UManagementBuilding>();
		NewManagementBuilding->Initialize(this);
		NewBuilding = Cast<UBuilding>(NewManagementBuilding);
		break;
		}
	default:
		break;
	}
	Buildings.Add(NewBuilding);
	OnCreateBuilding.Broadcast(NewBuilding, NewBuilding->GetBuildingType(), true);
	return NewBuilding;
}

UBuilding* APlanet::UpgradeBuilding(UBuilding* Building)
{
	if (Buildings.Contains(Building))
	{
		int32 Level = 0;
		float Cost = Building->GetBuildingLevelData().UpgpadeCost;
		for (int32 i = 0; i < Buildings.Num(); i++)
		{
			if (Buildings[i]->BuildingType == EBuildingType::Management)
			{
				Level = Buildings[i]->GetBuildingLevel();
			}
		}
		if (Building->GetBuildingLevel() == 3 || OwningPlayerState->Metal < Cost) return nullptr;//UBuilding upgrade cost
		else if (((Building->GetBuildingLevel() >= Level) && (Building->GetBuildingType() != EBuildingType::Management)) || OwningPlayerState->Metal < Cost) return nullptr;
		OwningPlayerState->Metal -= Cost;
		Building->UpgrageLevel();
		if (Building->GetBuildingType() != EBuildingType::Extract)
		{
			OwningPlayerState->AddMetalIncome(Building->GetBuildingLevelData().LevelBuff);
			OwningPlayerState->AddEnergyIncome(1);
			if (Building->GetBuildingLevel() == 3)
			{
				OwningPlayerState->AddCarbonIncome(10);
			}
		}
	}
	return Building;
}
