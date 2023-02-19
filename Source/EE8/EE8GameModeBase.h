// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EE8GameModeBase.generated.h"

class ASpaceManager;

/**
 * 
 */
UCLASS()
class EE8_API AEE8GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASpaceManager> SpaceManagerClass;

	UPROPERTY(EditDefaultsOnly)
	int32 GenerationSeed = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 NumStars = 50;

protected:
	ASpaceManager* SpaceManager;

	virtual void BeginPlay() override;

	void InitializeSpace(int32 Seed, int32 CountOfStars);

};
