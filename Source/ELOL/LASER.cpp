// Fill out your copyright notice in the Description page of Project Settings.


#include "LASER.h"

// Sets default values
ALASER::ALASER()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/grafika/bullets/bullet.bullet'"));
	UStaticMesh* Asset = MeshAsset.Object;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(-90, 0, 0));
	Mesh->SetStaticMesh(Asset);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(0);

	RootComponent = Mesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Cap"));
	Capsule->SetRelativeLocation(FVector(0, 0, 0));
	Capsule->SetWorldRotation(FRotator(-90, 0, 0));
	Capsule->SetupAttachment(RootComponent);
	Capsule->InitCapsuleSize(30.5, 30.f);
}

// Called when the game starts or when spawned
void ALASER::BeginPlay()
{
	Super::BeginPlay();
	lifespan = 1000;
	Mesh->OnComponentHit.AddDynamic(this, &ALASER::OnHit);
	Mesh->SetPhysicsLinearVelocity(10000 * Mesh->GetUpVector());
}

void ALASER::Collision()
{
	GetWorld()->SpawnActor<AActor>(BoomType, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());
	GetWorld()->DestroyActor(this);
}

void ALASER::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HIT"));
		}
		Collision();
	}
}

// Called every frame
void ALASER::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddForce(10000 * Mesh->GetUpVector());
	lifespan--;
	if (lifespan < 0)
	{
		GetWorld()->DestroyActor(this);
	}
}

