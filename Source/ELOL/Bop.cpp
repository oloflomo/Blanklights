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
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CameraTemp = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTemp"));

	//Camera setup
	Camera->SetupAttachment(CameraRoot);
	CameraTemp->SetupAttachment(Camera);
	CameraRoot->SetupAttachment(Root);
	Root->SetWorldRotation(FRotator(0, 0, 0));
	Root->SetWorldLocation(GetActorLocation());
	CameraRoot->SetRelativeLocation(FVector(0, 0, 0));
	CameraRoot->SetRelativeRotation(FRotator(0, 0, 0));
	Camera->SetRelativeLocation(FVector(-200, 0, 0));
	Camera->SetRelativeRotation(FRotator(0, 0, 0));
	CameraTemp->SetRelativeLocation(FVector(0, 0, 0));
	CameraTemp->SetRelativeRotation(FRotator(0, 0, 0));

	CameraRadius = 200;
	Toggle = 0;
	delay = 0;

	RootComponent = Root;
}

void ABop::camlong(float movementdelta)
{
	if (Toggle == 0)
	{
		CameraTemp->SetRelativeRotation(FRotator(movementdelta, 0, 0));
		FRotator NewRotation = CameraTemp->GetComponentRotation();
		Camera->SetRelativeRotation(NewRotation);
		FVector Location = Camera->GetRelativeRotation().Vector();
		Camera->SetRelativeLocation(Location * -CameraRadius);
	}
}

void ABop::camlat(float movementdelta)
{
	if (Toggle == 0)
	{
		CameraTemp->SetRelativeRotation(FRotator(0, movementdelta, 0));
		FRotator NewRotation = CameraTemp->GetComponentRotation();
		Camera->SetRelativeRotation(NewRotation);
		FVector Location = Camera->GetRelativeRotation().Vector();
		Camera->SetRelativeLocation(Location * -CameraRadius);
	}
}

void ABop::CameraRadiusSwap(float movementdelta)
{
	if (Toggle == 0)
	{
		CameraRadius += movementdelta * 100;
		CameraRadius = std::max(double(CameraRadius), double(50));
		CameraRadius = std::min(double(CameraRadius), double(1000));
	}
}

void ABop::CameraToggleSwap()
{
	if (delay > 0)
	{
		Toggle = !Toggle;
		delay = -50;
		CameraRadius = 300;
		Camera->SetRelativeRotation(FRotator(0, 0, 0));
		Camera->SetRelativeLocation(FVector(-300, 0, 0));
	}
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
	delay++;
	if (delay > 1)
	{
		delay = 0;
	}
}

// Called to bind functionality to input
void ABop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAction("CameraToggle", IE_Pressed, this, &ABop::CameraToggleSwap);
	PlayerInputComponent->BindAxis("camlong", this, &ABop::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &ABop::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &ABop::CameraRadiusSwap);

}

