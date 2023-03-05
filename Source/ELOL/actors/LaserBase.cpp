// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBase.h"

// Sets default values
ALaserBase::ALaserBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldRotation(FRotator(-90, 0, 0));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(0);

	RootComponent = Mesh;
}

void ALaserBase::Collision()
{
	GetWorld()->SpawnActor<AActor>(BoomType, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());
	GetWorld()->DestroyActor(this);
}

void ALaserBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

// Called when the game starts or when spawned
void ALaserBase::BeginPlay()
{
	Super::BeginPlay();
	lifespan = 100;
	Mesh->OnComponentHit.AddDynamic(this, &ALaserBase::OnHit);
	Mesh->SetPhysicsLinearVelocity(10000 * Mesh->GetUpVector());
}

// Called every frame
void ALaserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddForce(10000 * Mesh->GetUpVector());
	lifespan--;
	if (lifespan < 0)
	{
		GetWorld()->DestroyActor(this);
	}
}

