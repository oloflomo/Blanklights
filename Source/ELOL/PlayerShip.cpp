// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Math/Vector.h"
#include<algorithm>

APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Camera->SetupAttachment(Mesh);

	RootComponent = Mesh;
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