// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ELOL/components/InventoryComponent.h"
#include "ELOL/components/WaypointComponent.h"
#include "ELOL/structs/InvItem.h"
#include "ELOL/structs/AmmoInvItem.h"
#include "Components/StaticMeshComponent.h"
#include "MobShip.generated.h"

UCLASS()
class ELOL_API AMobShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobShip();

	//Decisions

	UFUNCTION(BlueprintCallable)
		void InitFire();

	UFUNCTION(BlueprintCallable)
		void Chase();

	//events

	UFUNCTION()
		void Collision(double dmg);

	UFUNCTION()
		void Destruction();

	UFUNCTION(BlueprintImplementableEvent)
		void Destruction_BP();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh2;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UInventoryComponent* Inventory;

	//properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BulletType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BoomType;

public:	

	//variables
	UPROPERTY(EditAnywhere)
		double durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int FuelLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Cooldown;

	UPROPERTY()
		FVector warp_vec = FVector(1, 0, 0);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
