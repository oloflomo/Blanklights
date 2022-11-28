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
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawneds
	virtual void BeginPlay() override;



	//components
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BoomType;



	//variables
	UPROPERTY(EditAnywhere)
		int lifespan;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
