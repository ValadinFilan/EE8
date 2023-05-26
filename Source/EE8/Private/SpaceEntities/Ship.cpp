// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Ship.h"
#include "SpaceEntities/Planet.h"
#include "Player/StarPlayerState.h"
#include "Engine/Engine.h"

AShip::AShip() : Super()
{
	Velocity = 10.f;
	AvaliableOrbit = 200.f;
}

void AShip::Initialize(AStarPlayerState* PlayerState)
{
	OwningPlayerState = PlayerState;
}

void AShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetSpaceObject.IsValid() && TargetSpaceObject != ConnectionTraget)
	{
		const FVector Distance = TargetSpaceObject->GetActorLocation() - GetActorLocation();

		if (Distance.Length() > AvaliableOrbit)
		{
			const FVector CurentForwardVector = GetActorForwardVector();
			const FVector TargetForwardVector = Distance.GetSafeNormal();
			SetActorRotation(FMath::RInterpTo(CurentForwardVector.Rotation(), TargetForwardVector.Rotation(), DeltaSeconds, 1.3).Quaternion());

			const FVector VelocityVector = GetActorForwardVector() * Velocity * FMath::Pow(FMath::Abs(FVector::DotProduct(CurentForwardVector, TargetForwardVector)), 2.5);
			AddActorWorldOffset(VelocityVector);
			
		}
		else
		{
			ConnectionTraget = TargetSpaceObject;
			if (APlanet* Planet = Cast<APlanet>(ConnectionTraget))
			{
				OwningPlayerState->AddCapturedPlanet(Planet);
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Connection successfull"));
		}
	
	}
}

void AShip::GoTo(ASpaceObject* Target)
{
	TargetSpaceObject = Target;
}
