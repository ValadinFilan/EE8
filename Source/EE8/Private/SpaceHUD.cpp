// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceHUD.h"
#include "Widgets/MainMenuUWB.h"
#include "Widgets/PlanetUWB.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

	AStarPlayerState* StarPlayerState = GetOwningPlayerController()->GetPlayerState<AStarPlayerState>();

	for (TPair<EUIGameStates, TSubclassOf<UUserWidget>> GameWidgetClassPair : GameWidgetClasses)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(World, GameWidgetClassPair.Value);

		if (Widget)
		{
			Widget->AddToViewport();
			GameWidgets.Add(GameWidgetClassPair.Key, Widget);
			Widget->SetVisibility(ESlateVisibility::Hidden);

			//Bind and configure widget
			if (GameWidgetClassPair.Key == EUIGameStates::MainMenu)
			{
				UMainMenuUWB* MenuWidget = Cast<UMainMenuUWB>(Widget);
				if (StarPlayerState && MenuWidget)
				{
					//MenuWidget->InitializeMainMenu(this, StarPlayerState->GlobalPickingManager ? PickingPlayerState->GlobalPickingManager->Tracks.Num() : 0);
					//MenuWidget->RestartGame->OnClicked.AddDynamic(this, &APickingHUD::RestartGame);
				}
			}
			//Bind and configure widget
			else if (GameWidgetClassPair.Key == EUIGameStates::Planet)
			{
				UPlanetUWB* PlanetWidget = Cast<UPlanetUWB>(Widget);
				if (StarPlayerState && PlanetWidget)
				{
					PlanetWidget->ExitButton->OnClicked.AddDynamic(this, &ASpaceHUD::HideCurrentWidget);
				}
			}
		}
	}
}

void ASpaceHUD::SetUIState(EUIGameStates UIState)
{
	if (GameWidgets.Contains(UIState))
	{
		UUserWidget* ActiveWidget = GameWidgets[UIState];
		if (ActiveWidget)
		{
			AStarPlayerState* PlayerState = GetOwningPlayerController()->GetPlayerState<AStarPlayerState>();

			//Prepare widget
			if (UIState == EUIGameStates::Planet)
			{
				UPlanetUWB* PlanetWidget = Cast<UPlanetUWB>(GameWidgets[EUIGameStates::Planet]);
				if (PlayerState && PlanetWidget) {

				}
			}

			//Enable widget
			ActiveWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ASpaceHUD::HideCurrentWidget()
{
	//Disable widgets with another state
	if (GameWidgets.Contains(CurentUIGameState))
	{
		UUserWidget* CurrentWidget = GameWidgets[CurentUIGameState];
		if (CurrentWidget)
		{
			CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}