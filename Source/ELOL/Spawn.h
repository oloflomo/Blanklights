// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Spawn.generated.h"

UCLASS()
class ELOL_API ASpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	//properties
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Asteroid;

	//variables

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
