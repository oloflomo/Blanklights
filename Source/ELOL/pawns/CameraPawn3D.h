// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "CameraPawn3D.generated.h"

UCLASS()
class ELOL_API ACameraPawn3D : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn3D();

	//cam movement
	void camlong(float movementdelta);
	void camlat(float movementdelta);
	void CameraRadiusSwap(float movementdelta);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Root;

	//main camera
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		double CameraRadius;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
