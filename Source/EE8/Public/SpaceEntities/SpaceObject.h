// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceObject.generated.h"

UCLASS()
class EE8_API ASpaceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceObject();

	UPROPERTY(EditDefaultsOnly)
	UMaterial* MaterialBase;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* Material;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Initialize();

	virtual void CreateCosmetic();
};
