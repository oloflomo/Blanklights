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

	MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	MeshRoot->SetupAttachment(Root);
	Mesh2->SetupAttachment(MeshRoot);
	Mesh3->SetupAttachment(MeshRoot);
	Mesh1->SetStaticMesh(Asset1);
	Mesh2->SetStaticMesh(Asset2);
	Mesh3->SetStaticMesh(Asset3);
	MeshRoot->SetRelativeLocation(FVector(0, 0, 0));
	MeshRoot->SetRelativeRotation(FRotator(0, 0, 0));
	Mesh1->SetRelativeLocation(FVector(0, 0, 0));
	Mesh1->SetWorldRotation(FRotator(0, 0, 0));
	Mesh2->SetRelativeLocation(FVector(0, 0, 0));
	Mesh2->SetWorldRotation(FRotator(0, 0, 0));
	Mesh3->SetRelativeLocation(FVector(0, 0, 0));
	Mesh3->SetWorldRotation(FRotator(0, 0, 0));
	Mesh1->SetSimulatePhysics(true);
	Mesh2->SetSimulatePhysics(false);
	Mesh3->SetSimulatePhysics(false);
	Mesh1->SetEnableGravity(0);
	Mesh2->SetCanEverAffectNavigation(0);
	Mesh2->SetCanEverAffectNavigation(0);
	RootComponent = Root;
}

void APlayerShip::thrusting(float timedelta)
{
	FVector XUnit = Mesh1->GetRelativeRotation().Vector();
	Mesh1->AddForce(100000*timedelta*XUnit);
}

void APlayerShip::yawing(float timedelta)
{
	FVector YUnit = Mesh1->GetRightVector();
	Mesh1->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(1000000, 0, 0));
}

void APlayerShip::pitching(float timedelta)
{
	FVector ZUnit = Mesh1->GetUpVector();
	Mesh1->AddForceAtLocationLocal(timedelta * FVector(0, 0, 1), FVector(1000000, 0, 0));
}

void APlayerShip::rolling(float timedelta)
{
	FVector ZUnit = Mesh1->GetUpVector();
	Mesh1->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(0, 0, 1000000));
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraRoot->SetWorldLocation(Mesh1->GetComponentLocation());
	MeshRoot->SetWorldLocation(Mesh1->GetComponentLocation());
	MeshRoot->SetWorldRotation(Mesh1->GetComponentRotation());
}

void APlayerShip::InitFire()
{
	GetWorld()->SpawnActor<AActor>(BulletType, Mesh1->GetComponentLocation(), Mesh1->GetComponentRotation());
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::InitFire);
	PlayerInputComponent->BindAxis("thrust", this, &APlayerShip::thrusting);
	PlayerInputComponent->BindAxis("pitch", this, &APlayerShip::pitching);
	PlayerInputComponent->BindAxis("yaw", this, &APlayerShip::yawing);
	PlayerInputComponent->BindAxis("roll", this, &APlayerShip::rolling);
	PlayerInputComponent->BindAxis("camlong", this, &APlayerShip::camlong);
	PlayerInputComponent->BindAxis("camlat", this, &APlayerShip::camlat);
	PlayerInputComponent->BindAxis("scroll", this, &APlayerShip::CameraRadiusSwap);
}