// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "SpaceManager.generated.h"

class AStar;

USTRUCT(BlueprintType, Atomic)
struct FSpaceSpawnParameters
{
	GENERATED_BODY()

public: 

	FSpaceSpawnParameters() {}

	UPROPERTY(EditDefaultsOnly)
	int32 Seed = 100;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MinPlanets = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxPlanets = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 NumberOfStars = 0;

	UPROPERTY(EditDefaultsOnly)
	float WeldDistance = 40000;

	UPROPERTY(EditDefaultsOnly)
	float GalaxyRadius = 50000;

	UPROPERTY(EditDefaultsOnly)
	float SystemRadius = 3000;

	UPROPERTY(EditDefaultsOnly)
	float NearestNeighbourRadius = 20000;
};

USTRUCT(BlueprintType, Atomic)
struct FSystemData{
	GENERATED_BODY()

public:

	FSystemData() {};

	FSystemData(FTransform T, TArray<FVector> NN)
	{
		Transform = T;
		NearestNeighbours = NN;
	}

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<FVector> NearestNeighbours;
};

UCLASS()
class EE8_API ASpaceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpaceSpawnParameters)
	FSpaceSpawnParameters SpaceSpawnParameters;

	UFUNCTION()
	void OnRep_SpaceSpawnParameters();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStar> StarClass;

	void GenerateStarSystem();

	FTransform GetSystemTransform();

	TArray<FVector> CheckSystemTransform(FTransform SystemTransform);

	FSystemData GetCheckedSystemData();

	FRandomStream RStream;

	TArray<AStar*> Stars;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawningParameters(FSpaceSpawnParameters Parameters);

	void InitializeSpace();
};
