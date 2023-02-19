// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceManager.generated.h"

class AStar;
class APlanet;

USTRUCT(BlueprintType)
struct FSpaceSpawnParameters
{
	GENERATED_BODY()

public: 

	FSpaceSpawnParameters() {}

	UPROPERTY(EditDefaultsOnly)
	int32 Seed;

	UPROPERTY(EditDefaultsOnly)
	int32 CountOfStars;

	UPROPERTY(EditDefaultsOnly)
	int32 MinPlanets = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxPlanets = 10;

	UPROPERTY(EditDefaultsOnly)
	float GalaxyRadius = 50000;

	UPROPERTY(EditDefaultsOnly)
	float SystemRadius = 3000;
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

	UPROPERTY(EditDefaultsOnly)
	FSpaceSpawnParameters SpaceSpawnParameters;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlanet> PlanetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStar> StarClass;

	void GenerateStarSystem();

	FTransform GetSystemTransform();

	FTransform GetPlanetTransform(AStar* System, int32 Index);
	
	bool CheckSystemTransform(FTransform SystemTransform);

	FTransform GetCheckedSystemTransform();

	TArray<AStar*> Stars;
	TArray<APlanet*> Planets;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawningParameters(FSpaceSpawnParameters Parameters);

	void InitializeSpace();
};
