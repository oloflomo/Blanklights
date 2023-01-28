// Fill out your copyright notice in the Description page of Project Settings.


#include "workshopPawn.h"

AworkshopPawn::AworkshopPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/grafika/bullets/bullet.bullet'"));
	UStaticMesh* Asset = MeshAsset.Object;

	MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
	MeshRoot->SetupAttachment(Root);
	MeshRoot->SetRelativeLocation(FVector(0, 0, 0));
	MeshRoot->SetRelativeRotation(FRotator(0, 0, 0));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetStaticMesh(Asset);
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));
	Mesh->SetSimulatePhysics(false);

	MeshTemp = CreateDefaultSubobject<USceneComponent>(TEXT("MeshTemp"));
	MeshTemp->SetupAttachment(Mesh);
	MeshTemp->SetRelativeLocation(FVector(0, 0, 0));
	MeshTemp->SetRelativeRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}



//server
void AworkshopPawn::ServerXmove_Implementation(float timedelta)
{
	Xmove(timedelta);
}
bool AworkshopPawn::ServerXmove_Validate(float timedelta)
{
	return true;
}

void AworkshopPawn::ServerYmove_Implementation(float timedelta)
{
	Ymove(timedelta);
}
bool AworkshopPawn::ServerYmove_Validate(float timedelta)
{
	return true;
}



// Player actions

void AworkshopPawn::Xmove(float movementdelta)
{
	FVector XUnit = Mesh->GetRelativeRotation().Vector();
	Mesh->SetWorldLocation(movementdelta * FVector(0, 0, 10) + Mesh->GetComponentLocation());
}

void AworkshopPawn::Ymove(float movementdelta)
{
	FVector YUnit = Mesh->GetRightVector();
	Mesh->SetWorldLocation(movementdelta * FVector(0, 10, 0) + Mesh->GetComponentLocation());
}

void AworkshopPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraRoot->SetWorldLocation(Mesh->GetComponentLocation());
	MeshRoot->SetWorldLocation(Mesh->GetComponentLocation());
	MeshRoot->SetWorldRotation(Mesh->GetComponentRotation());
}

void AworkshopPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AworkshopPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAxis("pitch", this, &AworkshopPawn::ServerXmove);
	PlayerInputComponent->BindAxis("yaw", this, &AworkshopPawn::ServerYmove);
}