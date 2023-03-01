// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"

// Sets default values
ARocket::ARocket()
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

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Cap"));
	Capsule->SetRelativeLocation(FVector(0, 0, 0));
	Capsule->SetWorldRotation(FRotator(-90, 0, 0));
	Capsule->SetupAttachment(RootComponent);
	Capsule->InitCapsuleSize(30.5, 30.f);
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	lifespan = 400;
	Mesh->OnComponentHit.AddDynamic(this, &ARocket::OnHit);
	Mesh->SetPhysicsLinearVelocity(100 * Mesh->GetUpVector());
}

void ARocket::Collision()
{
	GetWorld()->SpawnActor<AActor>(BoomType, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());
	//explode
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerShipClass, FoundActors);
	for (AActor* i : FoundActors) {
		APlayerShipBase* Ship = Cast<APlayerShipBase>(i);
		FVector vec = Ship->GetActorLocation() - this->GetActorLocation();
		double dist = vec.Length();
		if (dist < 10000)
		{
			Ship->Collision((double(1)/dist)*double(10000));
		}
	}
	GetWorld()->DestroyActor(this);
}

void ARocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddForce(10000 * Mesh->GetUpVector());
	lifespan--;
	if (lifespan < 0)
	{
		Collision();
	}
}

