// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "MapSpawn.generated.h"

UCLASS()
class ELOL_API AMapSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	//properties
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Asteroid;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Pick;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> WAYPNT;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> FogSpawner;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MobShip;

	//variables

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
