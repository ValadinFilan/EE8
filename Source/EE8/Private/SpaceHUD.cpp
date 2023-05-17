// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceHUD.h"
#include "Widgets/MainMenuUWB.h"
#include "Widgets/PlanetUWB.h"
#include "Widgets/SystemOverviewUWB.h"
#include "Widgets/BuildingUWB.h"
#include "Widgets/BuildingIconUWB.h"
#include "Widgets/CreateBuildingUWB.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "Player/StarPlayerController.h"
#include "SpaceEntities/Buildings/Building.h"
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
					PlanetWidget->ExitButton->OnClicked.AddUniqueDynamic(this, &ASpaceHUD::HideCurrentWidget);
					PlanetWidget->ExitButton->OnClicked.AddUniqueDynamic(Cast<AStarPlayerController>(GetOwningPlayerController()), &AStarPlayerController::DisolveSpaceSnapping);//Verify same function isn't already bound 
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
			//Bind and configure widget
			else if (GameWidgetClassPair.Key == EUIGameStates::Building)
			{
				UBuildingUWB* BuildingWidget = Cast<UBuildingUWB>(Widget);
				if (StarPlayerState && BuildingWidget)
				{
					BuildingWidget->ExitButton->OnClicked.AddUniqueDynamic(this, &ASpaceHUD::HideCurrentWidget);
					BuildingWidget->ExitButton->OnClicked.AddUniqueDynamic(this, &ASpaceHUD::SetUIStatePlanet);
					//BuildingWidget->InitializeBuildingWidget();
				}
			}
			//Bind and configure widget
			else if (GameWidgetClassPair.Key == EUIGameStates::CreateBuilding)
			{
				UCreateBuildingUWB* CreateBuildingWidget = Cast<UCreateBuildingUWB>(Widget);
				if (StarPlayerState && CreateBuildingWidget)
				{
					CreateBuildingWidget->ExitButton->OnClicked.AddUniqueDynamic(this, &ASpaceHUD::HideCurrentWidget);
					CreateBuildingWidget->ExitButton->OnClicked.AddUniqueDynamic(Cast<UPlanetUWB>(GameWidgets[EUIGameStates::Planet]), &UPlanetUWB::UnhideBuildingTable);
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
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
			GameWidgets[CurentUIGameState]->SetVisibility(ESlateVisibility::Hidden);
			AStarPlayerState* PlayerState = GetOwningPlayerController()->GetPlayerState<AStarPlayerState>();

			//Prepare widget
			if (UIState == EUIGameStates::Planet)
			{
				UPlanetUWB* PlanetWidget = Cast<UPlanetUWB>(GameWidgets[EUIGameStates::Planet]);
				if (AStarPlayerController* PlayerController = Cast<AStarPlayerController>(GetOwningPlayerController()); 
					PlanetWidget && PlayerController->CurrentPlanet.IsValid())
				{
					PlanetWidget->BuildingTable->SetVisibility(ESlateVisibility::Visible);
					PlanetWidget->InitializePlanetWidget(PlayerController->CurrentPlanet.Get());
					for (UBuildingIconUWB* BuildingIconWidget : PlanetWidget->BuildingIconWidgets)
					{
						BuildingIconWidget->OnButtonClicked.AddUObject(this, &ASpaceHUD::SetUIState);
						//PlanetWidget->GetPlanet()->OnCreateBuilding.AddUObject(BuildingIconWidget, &UBuildingIconUWB::InitializeIconWidget);
					}
				}
				CurentUIGameState = EUIGameStates::Planet;
			}

			//Prepare widget
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

void ASpaceHUD::SetUIState(EUIGameStates UIState, UBuilding* Building, UBuildingIconUWB* BuildingIconWidget)
{
	if (GameWidgets.Contains(UIState))
	{
		UUserWidget* ActiveWidget = GameWidgets[UIState];
		if (ActiveWidget)
		{
			GameWidgets[CurentUIGameState]->SetVisibility(ESlateVisibility::Hidden);
			AStarPlayerState* PlayerState = GetOwningPlayerController()->GetPlayerState<AStarPlayerState>();

			//Prepare widget
			if (UIState == EUIGameStates::CreateBuilding)
			{
				UPlanetUWB* PlanetWidget = Cast<UPlanetUWB>(GameWidgets[EUIGameStates::Planet]);
				PlanetWidget->BuildingTable->SetVisibility(ESlateVisibility::Hidden);

				UCreateBuildingUWB* CreateBuildingWidget = Cast<UCreateBuildingUWB>(GameWidgets[EUIGameStates::CreateBuilding]);
				CreateBuildingWidget->InitializeCreateBuildingWidget(PlanetWidget->GetPlanet(), BuildingIconWidget);
				CurentUIGameState = EUIGameStates::CreateBuilding;
			}

			if (UIState == EUIGameStates::Building)
			{
				UBuildingUWB* BuildingWidget = Cast<UBuildingUWB>(GameWidgets[EUIGameStates::Building]);
				BuildingWidget->InitializeBuildingWidget(Building);
				CurentUIGameState = EUIGameStates::Building;
			}

			//Enable widget
			ActiveWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ASpaceHUD::SetUIStatePlanet()
{
	SetUIState(EUIGameStates::Planet);
}

void ASpaceHUD::HideCurrentWidget()
{
	//Hide widget
	if (GameWidgets.Contains(CurentUIGameState))
	{
		UUserWidget* CurrentWidget = GameWidgets[CurentUIGameState];
		if (CurrentWidget)
		{
			CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		//Cast<AStarPlayerController>(GetOwningPlayerController())->DisolveSpaceSnapping();
	}
}