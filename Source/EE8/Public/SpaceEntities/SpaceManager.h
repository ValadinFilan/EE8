// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "SpaceManager.generated.h"

class AStar;

USTRUCT(BlueprintType)
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
	int32 NumberOfStars;

	UPROPERTY(EditDefaultsOnly)
	float WeldDistance = 40000;

	UPROPERTY(EditDefaultsOnly)
	float GalaxyRadius = 50000;

	UPROPERTY(EditDefaultsOnly)
	float SystemRadius = 3000;

	UPROPERTY(EditDefaultsOnly)
	float NearestNeighbourRadius = 20000;
};

UCLASS()
class EE8_API ASpaceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceManager();

protected:

	FLinearColor DrawColor = FLinearColor(1, 1, 1);

	ULineBatchComponent* LBComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FSpaceSpawnParameters SpaceSpawnParameters;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStar> StarClass;

	void GenerateStarSystem();

	FTransform GetSystemTransform();

	TArray<FVector> CheckSystemTransform(FTransform SystemTransform);

	FTransform GetCheckedSystemData();

	void DrawConnectionWithStars();

	FRandomStream RStream;

	UPROPERTY(BlueprintReadWrite)
	TArray<AStar*> Stars;

	TArray<FVector> Connections;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawningParameters(FSpaceSpawnParameters Parameters);

	void InitializeSpace();
};
