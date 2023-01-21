// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bop.h"
#include "WorkshopPawn.generated.h"

UCLASS()
class ELOL_API AWorkshopPawn : public ABop
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorkshopPawn();

	// Player Actions
	void X_move(float movementdelta);
	void Y_move(float movementdelta);
	virtual void CameraToggleSwap();


	//server
	UFUNCTION(server, unreliable, WithValidation)
		void ServerX_move(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void ServerY_move(float movementdelta);

protected:

	// Called when the game starts or when spawneds
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		USceneComponent* MeshRoot;

	UPROPERTY(EditAnywhere)
		USceneComponent* MeshTemp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh1;



public:

	//overrides
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
