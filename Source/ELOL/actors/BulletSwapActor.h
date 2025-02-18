// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BulletSwapActor.generated.h"

UCLASS()
class ELOL_API ABulletSwapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletSwapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
