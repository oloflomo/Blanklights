// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bop.h"
#include "Components/StaticMeshComponent.h"
#include<algorithm>
#include "Math/Vector.h"
#include "Components/CapsuleComponent.h"
#include "workshopPawn.generated.h"

/**
 * 
 */
UCLASS()
class ELOL_API AworkshopPawn : public ABop
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AworkshopPawn();

	// Player Actions
	void Xmove(float movementdelta);
	void Ymove(float movementdelta);

	//server
	UFUNCTION(server, unreliable, WithValidation)
		void ServerXmove(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void ServerYmove(float movementdelta);

protected:

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		USceneComponent* MeshRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* MeshTemp;

	//properties

	//variables

public:

	//overrides
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
