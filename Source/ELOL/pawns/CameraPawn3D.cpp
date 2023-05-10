// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn3D.h"
#include "GenericPlatform/GenericPlatformMath.h"

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

	RootComponent = Root;
}

void ACameraPawn3D::camlong(float movementdelta)
{
	switch (Mode)
	{
	case 0:
	{
		FRotator Rotation = Camera->GetRelativeRotation();
		double pitch = Rotation.Pitch;
		if (pitch > -70 && pitch < 70)
		{
			Camera->AddLocalRotation(FRotator(movementdelta, 0, 0));
			FVector Location = Camera->GetRelativeRotation().Vector();
			Camera->SetRelativeLocation(Location * -CameraRadius);
		}
		break;
	}
	case 1:
	{
		FRotator Rotation = Camera->GetRelativeRotation();
		double pitch = Rotation.Pitch;
		if (pitch > -70 && pitch < 70)
		{
			Camera->AddLocalRotation(FRotator(movementdelta, 0, 0));
			FVector Location = Camera->GetRelativeRotation().Vector();
			Camera->SetRelativeLocation(Location * -CameraRadius);
		}
		break;
	}
	case 2:
	{
		FRotator Rotation = Camera->GetRelativeRotation();
		double pitch = Rotation.Pitch;
		if (pitch > -70 && pitch < 70)
		{
			Camera->AddLocalRotation(FRotator(movementdelta, 0, 0));
			FVector Location = Camera->GetRelativeRotation().Vector();
			Camera->SetRelativeLocation(Location * -CameraRadius);
		}
		break;
	}
	default:
		break;
	}
}

void ACameraPawn3D::camlat(float movementdelta)
{
	switch (Mode)
	{
	case 0:
	{
		Camera->AddLocalRotation(FRotator(0, movementdelta, 0));
		FVector Location = Camera->GetRelativeRotation().Vector();
		Camera->SetRelativeLocation(Location * -CameraRadius);
		break;
	}
	case 1:
	{
		Camera->AddLocalRotation(FRotator(0, movementdelta, 0));
		FVector Location = Camera->GetRelativeRotation().Vector();
		Camera->SetRelativeLocation(Location * -CameraRadius);
		break;
	}
	case 2:
	{
		Camera->AddLocalRotation(FRotator(0, movementdelta, 0));
		FVector Location = Camera->GetRelativeRotation().Vector();
		Camera->SetRelativeLocation(Location * -CameraRadius);
		break;
	}
	default:
		break;
	}
}

void ACameraPawn3D::CameraRadiusSwap(float movementdelta)
{
	switch (Mode)
	{
	case 0:
	{
		CameraRadius += movementdelta * 100;
		CameraRadius = std::max(double(CameraRadius), double(50));
		CameraRadius = std::min(double(CameraRadius), double(1000));
		break;
	}
	case 1:
	{
		CameraRadius += movementdelta * 100;
		CameraRadius = std::max(double(CameraRadius), double(50));
		CameraRadius = std::min(double(CameraRadius), double(1000));
		break;
	}
	case 2:
	{
		CameraRadius += movementdelta * 100;
		CameraRadius = std::max(double(CameraRadius), double(50));
		CameraRadius = std::min(double(CameraRadius), double(1000));
		break;
	}
	default:
		break;
	}
}

// Called when the game starts or when spawned
void ACameraPawn3D::BeginPlay()
{
	Super::BeginPlay();
	Mode = 0;
	CameraRadius = 200;
}

// Called every frame
void ACameraPawn3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator Rotation = Camera->GetRelativeRotation();
	double roll = Rotation.Roll;
	Camera->AddLocalRotation(FRotator(0, 0, -roll));

	switch (Mode)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		break;
	}
	case 2:
	{
		break;
	}
	default:
		break;
	}
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

