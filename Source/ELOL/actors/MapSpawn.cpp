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




	//SITES



	//AllSites

	int limit = FMath::RandRange(int(50), int(100));
	for (int k = 0; k < limit; k++)
	{
		double center_x_component = FMath::RandRange(double(0), double(2 * Mapsize));
		double center_y_component = FMath::RandRange(double(-Mapsize), double(Mapsize));
		double center_z_component = FMath::RandRange(double(Mapsize - Mapsize/5), double(Mapsize + Mapsize/5));
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
				{
					int rr = FMath::RandRange(int(0), int(5));
					GetWorld()->SpawnActor<AActor>(DebrisActors[rr], FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				}
				else if (r < 90)
					GetWorld()->SpawnActor<AActor>(MobShip, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else
					GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
			}
		}
	}





	//BigSites

	for (int k = 0; k < 2; k++)
	{
		double center_x_component = FMath::RandRange(double(0), double(2 * Mapsize));
		double center_y_component = FMath::RandRange(double(-Mapsize), double(Mapsize));
		double center_z_component = FMath::RandRange(double(Mapsize - Mapsize / 5), double(Mapsize + Mapsize / 5));
		if (true) //collision check placeholder
		{
			for (int i = 0; i < 2000; i++)
			{
				double x_component = center_x_component + FMath::RandRange(int(-800000), int(800000));
				double y_component = center_y_component + FMath::RandRange(int(-800000), int(800000));
				double z_component = center_z_component + FMath::RandRange(int(-800000), int(800000));
				int r = FMath::RandRange(int(1), int(100));
				if (i <= 45)
					GetWorld()->SpawnActor<AActor>(WAYPNT, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else if (i < 50)
					GetWorld()->SpawnActor<AActor>(FogSpawner, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else if (r < 80)
				{
					int rr = FMath::RandRange(int(0), int(5));
					GetWorld()->SpawnActor<AActor>(DebrisActors[rr], FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				}
				else if (r < 90)
					GetWorld()->SpawnActor<AActor>(MobShip, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
				else
					GetWorld()->SpawnActor<AActor>(Pick, FVector(x_component, y_component, z_component), RootComponent->GetComponentRotation());
			}
		}
	}





	//PLANETS
	//sun
	GetWorld()->SpawnActor<AActor>(PlanetActors[0], FVector(Mapsize, 0, Mapsize), RootComponent->GetComponentRotation());
	//planets
	int count = FMath::RandRange(int(3), int(10));
	for (int k = 0; k < count; k++)
	{
		double x_component = FMath::RandRange(double(0), double(2 * Mapsize));
		double y_component = FMath::RandRange(double(-Mapsize), double(Mapsize));
		if (true) //collision check placeholder
		{
			int rr = FMath::RandRange(int(1), int(5));
			GetWorld()->SpawnActor<AActor>(PlanetActors[rr], FVector(x_component, y_component, Mapsize), RootComponent->GetComponentRotation());
		}
	}
}

// Called every frame
void AMapSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

