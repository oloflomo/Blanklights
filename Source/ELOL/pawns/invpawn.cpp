// Fill out your copyright notice in the Description page of Project Settings.


#include "invpawn.h"

// Sets default values
Ainvpawn::Ainvpawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("MeshRoot"));
	Cam->SetRelativeRotation(FRotator(0, 0, 0));

	RootComponent = Cam;
}

//server
void Ainvpawn::ServerXmove_Implementation(float timedelta)
{
	Xmove(timedelta);
}
bool Ainvpawn::ServerXmove_Validate(float timedelta)
{
	return true;
}

void Ainvpawn::ServerYmove_Implementation(float timedelta)
{
	Ymove(timedelta);
}
bool Ainvpawn::ServerYmove_Validate(float timedelta)
{
	return true;
}

// Player actions

void Ainvpawn::Xmove(float movementdelta)
{
	FVector XUnit = Cam->GetRelativeRotation().Vector();
	Cam->SetWorldLocation(movementdelta * FVector(0, 0, 10) + Cam->GetComponentLocation());
}

void Ainvpawn::Ymove(float movementdelta)
{
	FVector YUnit = Cam->GetRightVector();
	Cam->SetWorldLocation(movementdelta * FVector(0, 10, 0) + Cam->GetComponentLocation());
}

void Ainvpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Ainvpawn::ShowEle()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	EleWidget->AddToViewport();
}

void Ainvpawn::HideEle()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = false;
	}

	EleWidget->RemoveFromViewport();
}

void Ainvpawn::BeginPlay()
{
	Super::BeginPlay();

	EleWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), EleWidgetClass);
}

// Called to bind functionality to input
void Ainvpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAxis("pitch", this, &Ainvpawn::ServerXmove);
	PlayerInputComponent->BindAxis("yaw", this, &Ainvpawn::ServerYmove);
	PlayerInputComponent->BindAction("Inv", IE_Pressed, this, &Ainvpawn::ShowEle);
	PlayerInputComponent->BindAction("Inv", IE_Released, this, &Ainvpawn::HideEle);
}