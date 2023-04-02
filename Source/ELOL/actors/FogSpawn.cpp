// Fill out your copyright notice in the Description page of Project Settings.


#include "FogSpawn.h"

// Sets default values
AFogSpawn::AFogSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetRelativeLocation(FVector(0, 0, 0));
	Root->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}

// Called when the game starts or when spawned
void AFogSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFogSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

