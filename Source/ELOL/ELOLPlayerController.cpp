// Fill out your copyright notice in the Description page of Project Settings.


#include "ELOLPlayerController.h"
#include "ELOL/ELOLGameInstance.h"
#include "Blueprint/UserWidget.h"

AELOLPlayerController::AELOLPlayerController()
{
    if (ExitMenuWidgetClass)
    {
        ExitMenuWidget = CreateWidget<UUserWidget>(this, ExitMenuWidgetClass);
    }
}

void AELOLPlayerController::SetupInputComponent()
{
    // Always call this.
    Super::SetupInputComponent();

    // This is initialized on startup, you can go straight to binding
    InputComponent->BindAction("ExitMenu", IE_Pressed, this, &AELOLPlayerController::ShowMenu);
    InputComponent->BindAction("ExitMenu", IE_Released, this, &AELOLPlayerController::HideMenu);
}

void AELOLPlayerController::ShowMenu()
{
    if (ExitMenuWidget)
    {
        ExitMenuWidget->AddToViewport();
    }
}

void AELOLPlayerController::HideMenu()
{
    if (ExitMenuWidget)
    {
        ExitMenuWidget->RemoveFromParent();
    }
}