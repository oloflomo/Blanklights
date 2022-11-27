// Fill out your copyright notice in the Description page of Project Settings.


#include "LASER.h"

// Sets default values
ALASER::ALASER()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/grafika/bullets/bullet.bullet'"));
	UStaticMesh* Asset = MeshAsset.Object;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(-90, 0, 0));
	Mesh->SetStaticMesh(Asset);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(0);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ALASER::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALASER::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddForce(10000 * Mesh->GetUpVector());
}

