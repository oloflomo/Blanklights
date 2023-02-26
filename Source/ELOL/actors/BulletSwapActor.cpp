// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSwapActor.h"

// Sets default values
ABulletSwapActor::ABulletSwapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));
	Mesh->SetSimulatePhysics(false);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABulletSwapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletSwapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

