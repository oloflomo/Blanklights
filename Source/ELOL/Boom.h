// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
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
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		int lifespan;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};