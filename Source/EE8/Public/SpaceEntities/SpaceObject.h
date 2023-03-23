// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "SpaceObject.generated.h"

UCLASS()
class EE8_API ASpaceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceObject();

	UMaterialInterface* BaseMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ObjectMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* BaseDynamicMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRandomStream RStream;

	FVector Scale;

	UPROPERTY(BlueprintReadWrite)
	int32 RSeed;

	static double RandNormDist(double U1, double U2, double mu, double sigma);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Initialize();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateCosmetic();
};
