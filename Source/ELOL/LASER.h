// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "LASER.generated.h"

UCLASS()
class ELOL_API ALASER : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALASER();

	void Collision();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawneds
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
		int lifespan;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BoomType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
