// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueLaserActor.h"

// Sets default values
ABlueLaserActor::ABlueLaserActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/grafika/ateroid_pack/source/AsteroidsPackSF_Asteroid_no_1.AsteroidsPackSF_Asteroid_no_1'"));
	UStaticMesh* Asset = MeshAsset.Object;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));
	Mesh->SetStaticMesh(Asset);
	Mesh->SetSimulatePhysics(false);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABlueLaserActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlueLaserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

