// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Math/Vector.h"
#include<algorithm>

APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset1 = MeshAsset1.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset2(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset2 = MeshAsset2.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset3(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset3 = MeshAsset3.Object;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Camera->SetupAttachment(Root);
	Mesh1->SetupAttachment(Root);
	Mesh2->SetupAttachment(Root);
	Mesh3->SetupAttachment(Root);
	Mesh1->SetStaticMesh(Asset1);
	Mesh2->SetStaticMesh(Asset2);
	Mesh3->SetStaticMesh(Asset3);
	Mesh1->SetRelativeLocation(FVector(0, 0, 0));
	Mesh1->SetWorldRotation(FRotator(0, 0, 0));
	Mesh2->SetRelativeLocation(FVector(0, 0, 0));
	Mesh2->SetWorldRotation(FRotator(0, 0, 0));
	Mesh3->SetRelativeLocation(FVector(0, 0, 0));
	Mesh3->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}

void APlayerShip::thrusting(float movementdelta)
{
	//FVector NewLocation = GetActorLocation();
	//NewLocation.X += movementdelta;
	FVector XUnit = GetActorRotation().Vector();
	SetActorLocation(GetActorLocation() + movementdelta*XUnit);
}

void APlayerShip::yawing(float movementdelta)
{
	//FVector NewLocation = GetActorLocation();
	//NewLocation.Y += movementdelta;
	//SetActorLocation(NewLocation);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll += movementdelta;
	SetActorRotation(NewRotation);
	//FQuat RotationInput = FQuat(FRotator(0, movementdelta, 0));
	//AddActorWorldRotation(RotationInput);
	//AddActorLocalTransform
	//AddActorLocalRotation
}

void APlayerShip::pitching(float movementdelta)
{
	//FVector NewLocation = GetActorLocation();
	//NewLocation.Z += movementdelta;
	//SetActorLocation(NewLocation);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += movementdelta;
	SetActorRotation(NewRotation);
	//FQuat RotationInput = FQuat(FRotator(movementdelta, 0, 0));
	//AddActorWorldRotation(RotationInput);
	//AddActorLocalRotation(RotationInput, false, 0, ETeleportType::None);
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAxis("thrust", this, &APlayerShip::thrusting);
	PlayerInputComponent->BindAxis("pitch", this, &APlayerShip::pitching);
	PlayerInputComponent->BindAxis("yaw", this, &APlayerShip::yawing);
	PlayerInputComponent->BindAxis("camlong", this, &APlayerShip::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &APlayerShip::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &APlayerShip::CameraRadiusSwap);
}