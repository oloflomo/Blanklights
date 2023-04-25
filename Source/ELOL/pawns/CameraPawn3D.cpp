// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn3D.h"

// Sets default values
ACameraPawn3D::ACameraPawn3D()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	//Camera setup
	Root->SetWorldRotation(FRotator(0, 0, 0));

	Camera->SetupAttachment(Root);
	Camera->SetRelativeLocation(FVector(-200, 0, 0));
	Camera->SetRelativeRotation(FRotator(0, 0, 0));

	CameraRadius = 200;

	delay = 100;

	RootComponent = Root;
}

void ACameraPawn3D::camlong(float movementdelta)
{
	Camera->AddLocalRotation(FRotator(movementdelta, 0, 0));
	FVector Location = Camera->GetRelativeRotation().Vector();
	Camera->SetRelativeLocation(Location * -CameraRadius);
}

void ACameraPawn3D::camlat(float movementdelta)
{
	Camera->AddLocalRotation(FRotator(0, movementdelta, 0));
	FVector Location = Camera->GetRelativeRotation().Vector();
	Camera->SetRelativeLocation(Location * -CameraRadius);
}

void ACameraPawn3D::CameraRadiusSwap(float movementdelta)
{
	CameraRadius += movementdelta * 100;
	CameraRadius = std::max(double(CameraRadius), double(50));
	CameraRadius = std::min(double(CameraRadius), double(1000));
}

// Called when the game starts or when spawned
void ACameraPawn3D::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraPawn3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator Rotation = Camera->GetRelativeRotation();
	//double roll = Rotation.Roll;
	//double pitch = Rotation.Pitch;
	//double yaw = Rotation.Yaw;
	//if (delay < 20)
	//{
	//	Camera->AddLocalRotation(FRotator(0, 0, -roll/10));
	//}
	//delay -= 1;
	//if (delay < 0)
	//{
	//	delay = 80;
	//}
}

// Called to bind functionality to input
void ACameraPawn3D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAxis("camlong", this, &ACameraPawn3D::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &ACameraPawn3D::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &ACameraPawn3D::CameraRadiusSwap);

}

