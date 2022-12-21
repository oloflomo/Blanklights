// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn.h"


// Sets default values
ASpawn::ASpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetRelativeLocation(FVector(0, 0, 0));
	Root->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}

// Called when the game starts or when spawned
void ASpawn::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 1000; i++)
	{
		int x_component = FMath::RandRange(int(-100000), int(100000));
		int y_component = FMath::RandRange(int(-100000), int(100000));
		int z_component = FMath::RandRange(int(-100000), int(100000));
		GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
}

// Called every frame
void ASpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

