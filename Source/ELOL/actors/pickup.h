// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ELOL/Pawns/PlayerShipBase.h"
#include "pickup.generated.h"

UCLASS()
class ELOL_API Apickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Apickup();

	UFUNCTION()
		void Pick(AActor* other);

	UFUNCTION()
		void NoPick(AActor* other);

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Capsule;

	//properties
	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerShipBase> PlayerShipClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UInventoryComponent* Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UInvItem> ItemClass1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
