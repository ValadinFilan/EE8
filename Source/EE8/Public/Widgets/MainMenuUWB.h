// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUWB.generated.h"

class ASpaceHUD;
class UButton;
class UTextLayoutWidget;
class UImage;

/**
 * 
 */
UCLASS()
class EE8_API UMainMenuUWB : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* PlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* InfoButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ExitButton;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UPanelWidget* ButtonPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UImage* LogoImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextLayoutWidget* TextBox;

	void InitializeMainMenu(ASpaceHUD* HUD);

};
