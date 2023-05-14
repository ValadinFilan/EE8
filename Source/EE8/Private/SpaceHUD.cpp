// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceHUD.h"
#include "Widgets/MainMenuUWB.h"
#include "Widgets/PlanetUWB.h"
#include "Widgets/SystemOverviewUWB.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "Player/StarPlayerController.h"
#include "SpaceEntities/Planet.h"
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
			//Bind and configure widget
			else if (GameWidgetClassPair.Key == EUIGameStates::SystemOverview)
			{
				USystemOverviewUWB* SystemOverviewWidget = Cast<USystemOverviewUWB>(Widget);
				if (StarPlayerState && SystemOverviewWidget)
				{
					SystemOverviewWidget->InitializeSystemOverviewWidget(StarPlayerState);
					///PlanetWidget->ExitButton->OnClicked.AddDynamic(this, &ASpaceHUD::HideCurrentWidget);
					//PlanetWidget->ExitButton->OnClicked.AddDynamic(Cast<AStarPlayerController>(GetOwningPlayerController()), &AStarPlayerController::DisolveSpaceSnapping());
					//Cast<AStarPlayerController>(GetOwningPlayerController())->DisolveSpaceSnapping();
				}
			}
		}
	}
	SetUIState(EUIGameStates::SystemOverview);
}

void ASpaceHUD::SetUIState(EUIGameStates UIState)
{
	if (GameWidgets.Contains(UIState))
	{
		UUserWidget* ActiveWidget = GameWidgets[UIState];
		if (ActiveWidget)
		{
			GameWidgets[CurentUIGameState]->SetVisibility(ESlateVisibility::Hidden);
			AStarPlayerState* PlayerState = GetOwningPlayerController()->GetPlayerState<AStarPlayerState>();

			//Prepare widget
			if (UIState == EUIGameStates::Planet)
			{
				UPlanetUWB* PlanetWidget = Cast<UPlanetUWB>(GameWidgets[EUIGameStates::Planet]);
				if (AStarPlayerController* PlayerController = Cast<AStarPlayerController>(GetOwningPlayerController()); 
					PlanetWidget && PlayerController->CurrentPlanet.IsValid())
				{
					PlanetWidget->InitializePlanetWidget(PlayerController->CurrentPlanet.Get());
				}
				CurentUIGameState = EUIGameStates::Planet;
			}

			if (UIState == EUIGameStates::SystemOverview)
			{
				USystemOverviewUWB* SystemOverviewWidget = Cast<USystemOverviewUWB>(GameWidgets[EUIGameStates::SystemOverview]);
				CurentUIGameState = EUIGameStates::SystemOverview;
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
		Cast<AStarPlayerController>(GetOwningPlayerController())->DisolveSpaceSnapping();
	}
}