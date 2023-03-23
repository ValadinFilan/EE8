// Copyright Epic Games, Inc. All Rights Reserved.


#include "EE8GameModeBase.h"
#include "SpaceEntities/SpaceManager.h"
#include "Kismet/GameplayStatics.h"

void AEE8GameModeBase::BeginPlay()
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, FTimerDelegate::CreateWeakLambda(this,
		[this]()
		{
			InitializeSpace(GenerationSeed, NumStars);
		}), 1.0f, false);
}

void AEE8GameModeBase::InitializeSpace(int32 Seed, int32 NumberOfStars)
{
	SpaceManager = Cast<ASpaceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpaceManager::StaticClass()));

	if (SpaceManager) {
		FSpaceSpawnParameters SpaceParams;

		SpaceParams.Seed = Seed;
		SpaceParams.NumberOfStars = NumberOfStars;

		SpaceManager->SetSpawningParameters(SpaceParams);
		SpaceManager->InitializeSpace();
	}

}
