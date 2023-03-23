// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Ship.h"

AShip::AShip() : Super()
{
	Velocity = 10.f;
	AvaliableOrbit = 200.f;
}

void AShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetSpaceObject.IsValid())
	{
		const FVector Distance = TargetSpaceObject->GetActorLocation() - GetActorLocation();

		if (Distance.Length() > AvaliableOrbit)
		{
			const FVector CurentForwardVector = GetActorForwardVector();
			const FVector TargetForwardVector = Distance.GetSafeNormal();
			SetActorRotation(FMath::RInterpTo(CurentForwardVector.Rotation(), TargetForwardVector.Rotation(), DeltaSeconds, 0.9).Quaternion());
		
			const FVector VelocityVector = GetActorForwardVector() * Velocity * FMath::Abs(FVector::DotProduct(CurentForwardVector, TargetForwardVector));
			AddActorWorldOffset(VelocityVector);
			
		}
	
	}
}

void AShip::GoTo(ASpaceObject* Target)
{
	TargetSpaceObject = Target;
}
