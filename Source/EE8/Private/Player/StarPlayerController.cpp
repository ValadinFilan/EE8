// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StarPlayerController.h"
#include "Player/StarPlayerState.h"
#include "SpaceEntities/SpaceObject.h"
#include "SpaceEntities/Ship.h"

AStarPlayerController::AStarPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void AStarPlayerController::Tick(float DeltaSeconds)
{
	CurrentSpaceObject = TraceSpaceObject();
}

void AStarPlayerController::GetPlanetView()
{

}

void AStarPlayerController::SendShipToPlanet()
{
	if (CurrentShip.IsValid() && CurrentSpaceObject.IsValid())
	{
		CurrentShip->GoTo(CurrentSpaceObject.Get());
	}
}

void AStarPlayerController::GetFreeShip()
{
	AStarPlayerState* StarPlayerState = GetPlayerState<AStarPlayerState>();

	if (!StarPlayerState || StarPlayerState->PlayerShips.Num() < 1) return;

	CurrentShip = StarPlayerState->PlayerShips[0];

	SnapToSpaceObject(CurrentShip.Get());
}

void AStarPlayerController::GetFreePlanet()
{
	AStarPlayerState* StarPlayerState = GetPlayerState<AStarPlayerState>();

	if (!StarPlayerState || StarPlayerState->PlayerPlanets.Num() < 1) return;

	CurrentPlanet = StarPlayerState->PlayerPlanets[0];

	SnapToSpaceObject(CurrentPlanet.Get());
}

void AStarPlayerController::DisolveSpaceSnapping()
{
	UCameraComponent* ViewTargetCamera = Cast<UCameraComponent>(GetViewTarget()->GetComponentByClass(UCameraComponent::StaticClass()));
	
	if (ViewTargetCamera && GetPawn())
	{
		GetPawn()->SetActorLocation(ViewTargetCamera->GetComponentLocation());
		GetPawn()->SetActorRotation(ViewTargetCamera->GetComponentRotation());
	}

	SetViewTargetWithBlend(this, 0.7f);
}

void AStarPlayerController::SnapToSpaceObject(ASpaceObject* SpaceObject)
{
	SetViewTargetWithBlend(SpaceObject, 0.7f);
}

ASpaceObject* AStarPlayerController::TraceSpaceObject()
{
	float MouseX, MouseY;
	const bool CanGetMousePosition = GetMousePosition(MouseX, MouseY);

	if (CanGetMousePosition)
	{
		FHitResult HitResult;
		const bool bHit = GetHitResultAtScreenPosition(FVector2D(MouseX, MouseY), CurrentClickTraceChannel, true, HitResult);
		ASpaceObject* TracedActor = Cast<ASpaceObject>(HitResult.GetActor());
		
		if (bHit && TracedActor)
		{
			return TracedActor;
		}
	}

	return nullptr;
}
