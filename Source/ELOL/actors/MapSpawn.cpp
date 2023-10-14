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
	Mapsize = 100000000000;
	int limit = FMath::RandRange(int(50), int(100));
	for (int k = 0; k < limit; k++)
	{
		double center_x_component = FMath::RandRange(double(0), double(2 * Mapsize));
		double center_y_component = FMath::RandRange(double(-Mapsize), double(Mapsize));
		double center_z_component = FMath::RandRange(double(-Mapsize/5), double(Mapsize/5));
		if (true) //collision check placeholder
		{
			for (int i = 0; i < 50; i++)
			{
				double x_component = center_x_component + FMath::RandRange(int(-40000), int(40000));
				double y_component = center_y_component + FMath::RandRange(int(-40000), int(40000));
				double z_component = center_z_component + FMath::RandRange(int(-40000), int(40000));
				int r = FMath::RandRange(int(1), int(100));
				if (i == 0)
					GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else if (i < 3)
					GetWorld()->SpawnActor<AActor>(FogSpawner, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else if (r < 80)
					GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else if (r < 90)
					GetWorld()->SpawnActor<AActor>(MobShip, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else
					GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
			}
		}
	}
	for (int i = 0; i < 50; i++)
	{
		int x_component = FMath::RandRange(int(-40000), int(40000));
		int y_component = FMath::RandRange(int(-40000), int(40000));
		int z_component = FMath::RandRange(int(-40000), int(40000));
		int r = FMath::RandRange(int(1), int(100));
		if (i == 0)
			GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (i == 1)
			GetWorld()->SpawnActor<AActor>(FogSpawner, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 80)
			GetWorld()->SpawnActor<AActor>(Asteroid, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else if (r < 90)
			GetWorld()->SpawnActor<AActor>(MobShip, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
		else
			GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
	}
}

// Called every frame
void AMapSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

