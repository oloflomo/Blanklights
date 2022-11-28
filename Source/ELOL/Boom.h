// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SceneComponent.h"
#include "Boom.generated.h"

UCLASS()
class ELOL_API ABoom : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int lifespan;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ParticleFX1;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};