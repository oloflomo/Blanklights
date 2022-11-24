// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bop.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerShip.generated.h"

UCLASS()
class ELOL_API APlayerShip : public ABop
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

	// Delta movement
	void thrusting(float movementdelta);
	void yawing(float movementdelta);
	void pitching(float movementdelta);

protected:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

//public:
//	// Called to bind functionality to input
//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
};
