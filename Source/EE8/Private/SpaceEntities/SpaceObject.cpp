// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/SpaceObject.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ASpaceObject::ASpaceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->SetupAttachment(RootComponent);

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(ObjectMesh);
}

// Called when the game starts or when spawned
void ASpaceObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceObject::Initialize()
{
	if (!IsRunningDedicatedServer())
	{
		CreateCosmetic();
	}
}

void ASpaceObject::CreateCosmetic_Implementation()
{
	BaseMaterial = ObjectMesh->GetMaterial(0);
	BaseDynamicMaterial = ObjectMesh->CreateDynamicMaterialInstance(0, BaseMaterial);
	ObjectMesh->SetMaterial(0, BaseDynamicMaterial);
	BaseDynamicMaterial->SetScalarParameterValue(FName(TEXT("CosmeticSeed")), FMath::RandRange(0, 1));
}

double ASpaceObject::RandNormDist(double U1, double U2, double mu, double sigma)
{
	double result = FMath::Sqrt(-2 * log(U1)) * FMath::Cos(2 * PI * U2);
	result = result * sigma + mu;

	return result;
}