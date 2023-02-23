// Copyright Epic Games, Inc. All Rights Reserved.


#include "EE8GameModeBase.h"
#include "SpaceEntities/SpaceManager.h"

void AEE8GameModeBase::BeginPlay()
{
	InitializeSpace(GenerationSeed, NumStars);
}

void AEE8GameModeBase::InitializeSpace(int32 Seed, int32 NumberOfStars)
{
	SpaceManager = Cast<ASpaceManager>(GetWorld()->SpawnActor(SpaceManagerClass));

	if (SpaceManager) {
		FSpaceSpawnParameters SpaceParams;

		SpaceParams.Seed = Seed;
		SpaceParams.NumberOfStars = NumberOfStars;

		SpaceManager->SetSpawningParameters(SpaceParams);
		SpaceManager->InitializeSpace();
	}

}
