// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ELOLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ELOL_API AELOLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// ~Overrides: APlayerController
	virtual void SetupInputComponent() override;

	AELOLPlayerController();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UUserWidget* ExitMenuWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> ExitMenuWidgetClass;

	UFUNCTION()
		void ShowMenu();

	UFUNCTION()
		void HideMenu();
};