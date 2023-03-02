// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/ProgressBar.h"
#include "ELOL/ELOLGameInstance.h"
#include "invpawn.generated.h"

UCLASS()
class ELOL_API Ainvpawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Ainvpawn();

	// Player Actions
	void Xmove(float movementdelta);
	void Ymove(float movementdelta);
	void ShowEle();
	void HideEle();

	//server
	UFUNCTION(server, unreliable, WithValidation)
		void ServerXmove(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void ServerYmove(float movementdelta);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;

	UPROPERTY(EditAnywhere)
		UUserWidget* EleWidget;

	//properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> EleWidgetClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
