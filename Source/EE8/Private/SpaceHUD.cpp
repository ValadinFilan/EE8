// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceHUD.h"
#include "Blueprint/UserWidget.h"
#include "Player/StarPlayerState.h"

void ASpaceHUD::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ASpaceHUD::Initialize()
{
	UWorld* World = GetWorld();
	if (!World) return;

	//ASpacePlayerState* SpacePlayerState = GetOwningPlayerController()->GetPlayerState<ASpacePlayerState>();
}

void ASpaceHUD::SetUIState(EUIGameStates UIState)
{

}