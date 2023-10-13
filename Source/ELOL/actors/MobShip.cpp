// Fill out your copyright notice in the Description page of Project Settings.


#include "MobShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMobShip::AMobShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(0);

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(Mesh);
	//Mesh2->SetStaticMesh(Asset2);
	Mesh2->SetRelativeLocation(FVector(0, 0, 0));
	Mesh2->SetWorldRotation(FRotator(0, 0, 0));
	Mesh2->SetSimulatePhysics(false);

	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Mesh3->SetupAttachment(Mesh);
	//Mesh3->SetStaticMesh(Asset3);
	Mesh3->SetRelativeLocation(FVector(0, 0, 0));
	Mesh3->SetWorldRotation(FRotator(0, 0, 0));
	Mesh3->SetSimulatePhysics(false);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMobShip::BeginPlay()
{
	Super::BeginPlay();
	durability = 5;
	AmmoLeft = 50;
	FuelLeft = 5;
	Mesh->OnComponentHit.AddDynamic(this, &AMobShip::OnHit);
	Mesh2->OnComponentHit.AddDynamic(this, &AMobShip::OnHit);
	Mesh3->OnComponentHit.AddDynamic(this, &AMobShip::OnHit);
	Cooldown = 0;
	
}

// Called every frame
void AMobShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Cooldown == 0)
	{
		InitFire();
		Cooldown = 200;
	}
	else
	{
		Cooldown -= 1;
	}
	Chase();
}

void AMobShip::Collision(double dmg = 1)
{
	durability -= dmg;
	if (durability <= 0)
	{
		Destruction();
	}
}

void AMobShip::Destruction()
{
	if (BoomType)
	{
		GetWorld()->SpawnActor<AActor>(BoomType, GetActorLocation(), GetActorRotation());
	}
	Destruction_BP();
	GetWorld()->DestroyActor(this);
}

void AMobShip::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("CRASH"));
		}
		Collision();
	}
}

void AMobShip::InitFire()
{
	if (BulletType && AmmoLeft)
	{
		FVector FUnit = Mesh->GetForwardVector();
		FVector TUnit = Mesh->GetRightVector();
		FTransform SpawnTransform1 = FTransform(GetActorRotation(), GetActorLocation() + 1000 * FUnit + 40 * TUnit, FVector(1, 1, 1));
		FTransform SpawnTransform2 = FTransform(GetActorRotation(), GetActorLocation() + 1000 * FUnit - 40 * TUnit, FVector(1, 1, 1));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		GetWorld()->SpawnActor<AActor>(BulletType, SpawnTransform1, SpawnParameters);
		GetWorld()->SpawnActor<AActor>(BulletType, SpawnTransform2, SpawnParameters);
		AmmoLeft--;
	}
}

void AMobShip::Chase()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector SelfLocation = GetActorLocation();
	FVector Direction = PlayerLocation - SelfLocation;
	FRotator RotationDirection = Direction.Rotation() - GetActorRotation();
	double pitch = RotationDirection.Pitch;// / abs(RotationDirection.Pitch);
	double roll = RotationDirection.Roll;// / abs(RotationDirection.Roll);
	double yaw = RotationDirection.Yaw;// / abs(RotationDirection.Yaw);
	Mesh->AddForce(1000000 * GetActorRotation().Vector());
	//SetActorRotation(FRotator(pitch, roll, yaw) - GetActorRotation());
	SetActorRotation(Direction.Rotation());
	//Mesh->AddForceAtLocationLocal(FVector(0, 1, 0), FVector(10000000 * RotationDirection.Yaw, 0, 0)); //yaw
	//Mesh->AddForceAtLocationLocal(FVector(0, 0, 1), FVector(10000000 * RotationDirection.Pitch, 0, 0)); //pitch
	//Mesh->AddForceAtLocationLocal(FVector(0, 1, 0), FVector(0, 0, 10000000 * RotationDirection.Roll)); //roll
}