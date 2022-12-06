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
	MeshRoot->SetupAttachment(Root);
	MeshRoot->SetRelativeLocation(FVector(0, 0, 0));
	MeshRoot->SetRelativeRotation(FRotator(0, 0, 0));

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh1->SetupAttachment(Root);
	Mesh1->SetStaticMesh(Asset1);
	Mesh1->SetRelativeLocation(FVector(0, 0, 0));
	Mesh1->SetWorldRotation(FRotator(0, 0, 0));
	Mesh1->SetSimulatePhysics(true);
	Mesh1->SetEnableGravity(0);

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(MeshRoot);
	Mesh2->SetStaticMesh(Asset2);
	Mesh2->SetRelativeLocation(FVector(0, 0, 0));
	Mesh2->SetWorldRotation(FRotator(0, 0, 0));
	Mesh2->SetSimulatePhysics(false);

	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Mesh3->SetupAttachment(MeshRoot);
	Mesh3->SetStaticMesh(Asset3);
	Mesh3->SetRelativeLocation(FVector(0, 0, 0));
	Mesh3->SetWorldRotation(FRotator(0, 0, 0));
	Mesh3->SetSimulatePhysics(false);

	MeshTemp = CreateDefaultSubobject<USceneComponent>(TEXT("MeshTemp"));
	MeshTemp->SetupAttachment(Mesh1);
	MeshTemp->SetRelativeLocation(FVector(0, 0, 0));
	MeshTemp->SetRelativeRotation(FRotator(0, 0, 0));
	
	RootComponent = Root;
}






//events

void APlayerShip::Collision()
{
	durability -= 10;
}

void APlayerShip::Destruction()
{
	GetWorld()->SpawnActor<AActor>(BoomType, Mesh1->GetComponentLocation(), Mesh1->GetComponentRotation());
	GetWorld()->DestroyActor(this);
}

void APlayerShip::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRASH"));
		}
		Collision();
	}
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraRoot->SetWorldLocation(Mesh1->GetComponentLocation());
	MeshRoot->SetWorldLocation(Mesh1->GetComponentLocation());
	MeshRoot->SetWorldRotation(Mesh1->GetComponentRotation());

	if (Toggle == 1)
	{
		Camera->SetupAttachment(Mesh1);
		CameraRadius = 300;
		Camera->SetRelativeRotation(FRotator(0, 0, 0));
		Camera->SetRelativeLocation(FVector(-300, 0, 0));
	}

	if (durability < 0)
	{
		Destruction();
	}
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	durability = 30;
	Mesh1->OnComponentHit.AddDynamic(this, &APlayerShip::OnHit);
	Mesh2->OnComponentHit.AddDynamic(this, &APlayerShip::OnHit);
	Mesh3->OnComponentHit.AddDynamic(this, &APlayerShip::OnHit);
}

//server


void APlayerShip::Serverthrusting_Implementation(float timedelta)
{
	thrusting(timedelta);
}
bool APlayerShip::Serverthrusting_Validate(float timedelta)
{
	return true;
}

void APlayerShip::ServerInitFire_Implementation()
{
	InitFire();
}
bool APlayerShip::ServerInitFire_Validate()
{
	return true;
}

void APlayerShip::Serverpitching_Implementation(float timedelta)
{
	pitching(timedelta);
}
bool APlayerShip::Serverpitching_Validate(float timedelta)
{
	return true;
}

void APlayerShip::Serveryawing_Implementation(float timedelta)
{
	yawing(timedelta);
}
bool APlayerShip::Serveryawing_Validate(float timedelta)
{
	return true;
}

void APlayerShip::Serverrolling_Implementation(float timedelta)
{
	rolling(timedelta);
}
bool APlayerShip::Serverrolling_Validate(float timedelta)
{
	return true;
}

// Player actions

void APlayerShip::thrusting(float timedelta)
{
	FVector XUnit = Mesh1->GetRelativeRotation().Vector();
	Mesh1->AddForce(100000*timedelta*XUnit);
	//Controller.thrusting(1);
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

void APlayerShip::InitFire()
{
	MeshTemp->SetRelativeLocation(FVector(200, -50, 0));
	GetWorld()->SpawnActor<AActor>(BulletType, MeshTemp->GetComponentLocation(), Mesh1->GetComponentRotation());
	MeshTemp->SetRelativeLocation(FVector(200, 50, 0));
	GetWorld()->SpawnActor<AActor>(BulletType, MeshTemp->GetComponentLocation(), Mesh1->GetComponentRotation());
	MeshTemp->SetRelativeLocation(FVector(0, 0, 0));
}

void APlayerShip::CameraToggleSwap()
{
	//if (delay > 0)
	//{
		//if (Toggle == 1)
		//{
		//	Camera->SetupAttachment(CameraRoot);
		//	Toggle = !Toggle;
		//	delay = -50;
		//	CameraRadius = 300;
		//	Camera->SetRelativeRotation(FRotator(0, 0, 0));
		//	Camera->SetRelativeLocation(FVector(-300, 0, 0));
		//}
		//if (Toggle == 0)
		//{
			Camera->SetupAttachment(Mesh1);
			Toggle = 1;
			delay = -50;
			CameraRadius = 300;
			Camera->SetRelativeRotation(FRotator(0, 0, 0));
			Camera->SetRelativeLocation(FVector(-300, 0, 0));
		//}
	//}
}










// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::ServerInitFire);
	PlayerInputComponent->BindAxis("thrust", this, &APlayerShip::Serverthrusting);
	PlayerInputComponent->BindAxis("pitch", this, &APlayerShip::Serverpitching);
	PlayerInputComponent->BindAxis("yaw", this, &APlayerShip::Serveryawing);
	PlayerInputComponent->BindAxis("roll", this, &APlayerShip::Serverrolling);
}