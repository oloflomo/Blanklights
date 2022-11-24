// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Math/Vector.h"
#include<algorithm>

APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("/Script/Engine.StaticMesh'/Game/grafika/spaceship/spac3/sp2-1_Object134.sp2-1_Object134'"));
	UStaticMesh* Asset1 = MeshAsset1.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset2(TEXT("/Script/Engine.StaticMesh'/Game/grafika/spaceship/spac3/sp2-1_Object134_001.sp2-1_Object134_001'"));
	UStaticMesh* Asset2 = MeshAsset2.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset3(TEXT("/Script/Engine.StaticMesh'/Game/grafika/spaceship/spac3/sp2-1_Object134_002.sp2-1_Object134_002'"));
	UStaticMesh* Asset3 = MeshAsset3.Object;

	RotationRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationRoot"));
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	RotationRoot->SetupAttachment(Root);
	Mesh1->SetupAttachment(RotationRoot);
	Mesh2->SetupAttachment(RotationRoot);
	Mesh3->SetupAttachment(RotationRoot);
	Mesh1->SetStaticMesh(Asset1);
	Mesh2->SetStaticMesh(Asset2);
	Mesh3->SetStaticMesh(Asset3);
	RotationRoot->SetRelativeLocation(FVector(0, 0, 0));
	RotationRoot->SetRelativeRotation(FRotator(0, 0, 0));
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
	FVector XUnit = RotationRoot->GetRelativeRotation().Vector();
	SetActorLocation(GetActorLocation() + movementdelta*XUnit);
}

void APlayerShip::yawing(float movementdelta)
{
	//FVector NewLocation = GetActorLocation();
	//NewLocation.Y += movementdelta;
	//SetActorLocation(NewLocation);
	FRotator NewRotation = RotationRoot->GetRelativeRotation();
	NewRotation.Yaw += movementdelta;
	RotationRoot->SetRelativeRotation(NewRotation);
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
	FRotator NewRotation = RotationRoot->GetRelativeRotation();
	NewRotation.Pitch += movementdelta;
	RotationRoot->SetRelativeRotation(NewRotation);
	//FQuat RotationInput = FQuat(FRotator(movementdelta, 0, 0));
	//AddActorWorldRotation(RotationInput);
	//AddActorLocalRotation(RotationInput, false, 0, ETeleportType::None);
}

void APlayerShip::rolling(float movementdelta)
{
	//FVector NewLocation = GetActorLocation();
	//NewLocation.Z += movementdelta;
	//SetActorLocation(NewLocation);
	FRotator NewRotation = RotationRoot->GetRelativeRotation();
	NewRotation.Roll += movementdelta;
	RotationRoot->SetRelativeRotation(NewRotation);
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
	PlayerInputComponent->BindAxis("roll", this, &APlayerShip::rolling);
	PlayerInputComponent->BindAxis("camlong", this, &APlayerShip::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &APlayerShip::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &APlayerShip::CameraRadiusSwap);
}