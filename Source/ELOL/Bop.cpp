// Fill out your copyright notice in the Description page of Project Settings.


#include "Bop.h"
#include "Math/Vector.h"

// Sets default values
ABop::ABop()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Camera setup
	Camera->SetupAttachment(CameraMesh);
	Camera->SetRelativeLocation(FVector(-200, 0, 0));

	CameraRadius = 200;

	RootComponent = CameraMesh;
}

void ABop::xaxismove(float movementdelta)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X += movementdelta;
	SetActorLocation(NewLocation);
}

void ABop::yaxismove(float movementdelta)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Y += movementdelta;
	SetActorLocation(NewLocation);
	//FQuat RotationInput = FQuat(FRotator(0, movementdelta, 0));
	//AddActorWorldRotation(RotationInput);
	//AddActorLocalTransform
	//AddActorLocalRotation
}

void ABop::zaxismove(float movementdelta)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += movementdelta;
	SetActorLocation(NewLocation);
	//FQuat RotationInput = FQuat(FRotator(movementdelta, 0, 0));
	//AddActorWorldRotation(RotationInput);
	//AddActorLocalRotation(RotationInput, false, 0, ETeleportType::None);
}
///////////////////////////////////////////////////
void ABop::camlong(float movementdelta)
{
	FVector Location = Camera->GetRelativeLocation();
	FVector2D NewSphericalLocation = Location.UnitCartesianToSpherical(); // blah //radians
	NewSphericalLocation.X += movementdelta/100;
	FVector NewLocation = NewSphericalLocation.SphericalToUnitCartesian();
	Camera->SetRelativeLocation(NewLocation * CameraRadius);
	//Camera->SetRelativeLocation(Location);
	//Camera->SetRelativeRotation(FRotator(NewSphericalLocation.X * 57.296 - 90, NewSphericalLocation.Y * 57.296, 0));
	//FVector OloflomoLocation = GetActorLocation();
}

void ABop::camlat(float movementdelta)
{
	FVector Location = Camera->GetRelativeLocation();
	FVector2D NewSphericalLocation = Location.UnitCartesianToSpherical(); // blah //radians
	NewSphericalLocation.Y += movementdelta/100;
	FVector NewLocation = NewSphericalLocation.SphericalToUnitCartesian();
	Camera->SetRelativeLocation(NewLocation * CameraRadius);
	//Camera->SetRelativeLocation(Location);
	//Camera->SetRelativeRotation(FRotator(NewSphericalLocation.X * 57.296 - 90, NewSphericalLocation.Y * 57.296, 0));
	//FVector NewLocation = Camera->setrelative  GetRelativeTransform();
	//NewLocation.Y += movementdelta;
	//Camera->SetRelativeLocation(NewLocation);
	//FVector NewLocation = GetActorLocation();
	//NewLocation.Z += movementdelta;
	//SetActorLocation(NewLocation);
}

// Called when the game starts or when spawned
void ABop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAxis("thrust", this, &ABop::xaxismove);
	PlayerInputComponent->BindAxis("pitch", this, &ABop::zaxismove);
	PlayerInputComponent->BindAxis("yaw", this, &ABop::yaxismove);
	PlayerInputComponent->BindAxis("camlong", this, &ABop::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &ABop::camlat);
}

