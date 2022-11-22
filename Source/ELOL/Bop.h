// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Bop.generated.h"

UCLASS()
class ELOL_API ABop : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABop();

	// Delta movement
	void thrusting(float movementdelta);
	void yawing(float movementdelta);
	void pitching(float movementdelta);

	//cam movement
	void camlong(float movementdelta);
	void camlat(float movementdelta);
	void CameraRadiusSwap(float movementdelta);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//main camera
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CameraMesh;

	UPROPERTY(VisibleAnywhere)
		double CameraRadius;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
