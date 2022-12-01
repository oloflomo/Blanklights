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

	// Player Actions
	void thrusting(float movementdelta);
	void yawing(float movementdelta);
	void pitching(float movementdelta);
	void rolling(float movementdelta);
	void InitFire();
	virtual void CameraToggleSwap();

	//events

	void Collision();

	void Destruction();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

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

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh2;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BulletType;


	//properties
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BoomType;


	//variables
	UPROPERTY(EditAnywhere)
		int durability;

public:

	//overrides
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
