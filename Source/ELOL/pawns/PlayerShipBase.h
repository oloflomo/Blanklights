// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPawn3D.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerShipBase.generated.h"

/**
 *
 */
UCLASS()
class ELOL_API APlayerShipBase : public ACameraPawn3D
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShipBase(); // ?E?

	// Player Actions
	void thrusting(float movementdelta);
	void yawing(float movementdelta);
	void pitching(float movementdelta);
	void rolling(float movementdelta);
	void InitFire();
	void ShowInv();
	void HideInv();
	void ShowLoot();
	void HideLoot();

	//server
	UFUNCTION(server, unreliable, WithValidation)
		void Serverthrusting(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void ServerInitFire();
	UFUNCTION(server, unreliable, WithValidation)
		void Serverpitching(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void Serveryawing(float movementdelta);
	UFUNCTION(server, unreliable, WithValidation)
		void Serverrolling(float movementdelta);

	//events

	void Collision(double dmg);

	void Destruction();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	// Called when the game starts or when spawneds
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh2;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh3;

	UPROPERTY(EditAnywhere)
		UUserWidget* Widget;

	UPROPERTY(EditAnywhere)
		UUserWidget* InvWidget;

	UPROPERTY(EditAnywhere)
		UUserWidget* LootWidget;

	//properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BulletType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BoomType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> InvWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> LootWidgetClass;

	//variables
	UPROPERTY(EditAnywhere)
		double durability;

public:

	//overrides
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
