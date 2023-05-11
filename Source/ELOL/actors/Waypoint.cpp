// Fill out your copyright notice in the Description page of Project Settings.


#include "Waypoint.h"

// Sets default values
AWaypoint::AWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));

	Way_comp = CreateDefaultSubobject<UWaypointComponent>(TEXT("Wid_comp"));

	Way_comp->SetupAttachment(Mesh);
	Way_comp->SetRelativeLocation(FVector(0, 0, 0));
	Way_comp->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

