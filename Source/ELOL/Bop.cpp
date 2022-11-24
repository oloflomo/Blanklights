// Fill out your copyright notice in the Description page of Project Settings.


#include "Bop.h"
#include "Math/Vector.h"
#include<algorithm>

// Sets default values
ABop::ABop()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	//Camera setup
	Camera->SetupAttachment(Root);
	Root->SetWorldRotation(FRotator(0, 0, 0));
	Camera->SetRelativeLocation(FVector(-200, 0, 0));
	Camera->SetRelativeRotation(FRotator(0, 0, 0));

	CameraRadius = 200;

	RootComponent = Root;
}

void ABop::camlong(float movementdelta)
{
	FVector Location = Camera->GetRelativeLocation();
	Location /= CameraRadius;
	FVector2D NewSphericalLocation = Location.UnitCartesianToSpherical(); // blah //radians
	NewSphericalLocation.X += movementdelta/100;
	FVector NewLocation = NewSphericalLocation.SphericalToUnitCartesian();
	Camera->SetRelativeLocation(NewLocation * CameraRadius);
	Camera->SetRelativeRotation(FRotator(-90 + 57 * NewSphericalLocation.X, -180 + 57 * NewSphericalLocation.Y, 0));
}

void ABop::camlat(float movementdelta)
{
	FVector Location = Camera->GetRelativeLocation();
	Location /= CameraRadius;
	FVector2D NewSphericalLocation = Location.UnitCartesianToSpherical(); // blah //radians
	NewSphericalLocation.Y += movementdelta / 100;
	FVector NewLocation = NewSphericalLocation.SphericalToUnitCartesian();
	Camera->SetRelativeLocation(NewLocation * CameraRadius);
	Camera->SetRelativeRotation(FRotator(-90 + 57 * NewSphericalLocation.X, -180 + 57 * NewSphericalLocation.Y, 0));
}

void ABop::CameraRadiusSwap(float movementdelta)
{
	CameraRadius += movementdelta*100;
	CameraRadius = std::max(double(CameraRadius), double(50));
	CameraRadius = std::min(double(CameraRadius), double(1000));
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
	PlayerInputComponent->BindAxis("camlong", this, &ABop::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &ABop::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &ABop::CameraRadiusSwap);
}

