// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPawn3D.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ELOL/ELOLGameInstance.h"
#include "ELOL/components/InventoryComponent.h"
#include "ELOL/components/WaypointComponent.h"
#include "ELOL/structs/InvItem.h"
#include "ELOL/structs/AmmoInvItem.h"
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
	UFUNCTION()
		void thrusting(float movementdelta);
	UFUNCTION()
		void yawing(float movementdelta);
	UFUNCTION()
		void pitching(float movementdelta);
	UFUNCTION()
		void rolling(float movementdelta);
	UFUNCTION(BlueprintCallable)
		void InitFire();
	UFUNCTION()
		void ShowLoot(UInventoryComponent* ForeignInventory);
	UFUNCTION()
		void HideLoot();
	UFUNCTION()
		void SwapEngine();
	UFUNCTION()
		UInvItem* RollItem();

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
	
	UFUNCTION()
		void Collision(double dmg);

	UFUNCTION()
		void Destruction();

	UFUNCTION(BlueprintCallable, Category =  "Items")
		void UseItem(class UInvItem* InvItem);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowForeignInv(UInventoryComponent* ForeignInventory);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowLootBP();

	UFUNCTION(BlueprintImplementableEvent)
		void HideLootBP();

	UFUNCTION(BlueprintCallable)
		void Attachedcpp();

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UInventoryComponent* Inventory;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UWaypointComponent* Way_comp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UUserWidget* Widget;

	//properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BulletType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BoomType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UInvItem> ItemClass1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UInvItem> ItemClass2;

public:

	//variables
	UPROPERTY(EditAnywhere)
		double durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool EngineType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int FuelLeft;

	UPROPERTY()
		FVector warp_vec = FVector(1, 0, 0);

public:

	//overrides
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};