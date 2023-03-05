// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "LaserBase.generated.h"

UCLASS()
class ELOL_API ALaserBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserBase();

	void Collision();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	//properties
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BoomType;

	//variables
	UPROPERTY(EditAnywhere)
		int lifespan;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
