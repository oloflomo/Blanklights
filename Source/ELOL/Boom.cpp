// Fill out your copyright notice in the Description page of Project Settings.


#include "Boom.h"

// Sets default values
ABoom::ABoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/grafika/bullets/bullet.bullet'"));
	UStaticMesh* Asset = MeshAsset.Object;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));
	Mesh->SetStaticMesh(Asset);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetEnableGravity(0);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABoom::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}