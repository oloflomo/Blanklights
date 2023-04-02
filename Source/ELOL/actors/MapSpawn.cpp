// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSpawn.h"

// Sets default values
AMapSpawn::AMapSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetRelativeLocation(FVector(0, 0, 0));
	Root->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}

// Called when the game starts or when spawned
void AMapSpawn::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(20000), int(40000));
		int y_component = FMath::RandRange(int(20000), int(40000));
		int z_component = FMath::RandRange(int(20000), int(40000));
		int r = FMath::RandRange(int(1), int(100));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(-510000), int(-500000));
		int y_component = FMath::RandRange(int(-510000), int(-500000));
		int z_component = FMath::RandRange(int(-510000), int(-500000));
		int r = FMath::RandRange(int(1), int(100));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(-1510000), int(-1500000));
		int y_component = FMath::RandRange(int(-1510000), int(-1500000));
		int z_component = FMath::RandRange(int(-510000), int(-500000));
		int r = FMath::RandRange(int(1), int(1000));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(-1510000), int(-1500000));
		int y_component = FMath::RandRange(int(-1510000), int(-1500000));
		int z_component = FMath::RandRange(int(-1510000), int(-1500000));
		int r = FMath::RandRange(int(1), int(1000));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(-1510000), int(-1500000));
		int y_component = FMath::RandRange(int(-3510000), int(-3500000));
		int z_component = FMath::RandRange(int(-2510000), int(-2500000));
		int r = FMath::RandRange(int(1), int(1000));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
}

// Called every frame
void AMapSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

