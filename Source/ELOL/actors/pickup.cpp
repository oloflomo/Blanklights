// Fill out your copyright notice in the Description page of Project Settings.


#include "pickup.h"

// Sets default values
Apickup::Apickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetWorldRotation(FRotator(-90, 0, 0));
	Mesh->SetSimulatePhysics(false);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(Mesh);
	Capsule->InitCapsuleSize(100000.f, 100000.f);
	

	RootComponent = Mesh;
}

void Apickup::Pick()
{
	//pick
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerShipClass, FoundActors);
	for (AActor* i : FoundActors) {
		APlayerShipBase* Ship = Cast<APlayerShipBase>(i);
		FVector vec = Ship->GetActorLocation() - this->GetActorLocation();
		double dist = vec.Length();
		if (dist < 1000)
		{
			Ship->ShowLoot();
		}
	}
}

void Apickup::NoPick()
{
	//nopick
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerShipClass, FoundActors);
	for (AActor* i : FoundActors) {
		APlayerShipBase* Ship = Cast<APlayerShipBase>(i);
		FVector vec = Ship->GetActorLocation() - this->GetActorLocation();
		double dist = vec.Length();
		if (dist < 10000)
		{
			Ship->HideLoot();
		}
	}
}

// Called when the game starts or when spawned
void Apickup::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &Apickup::OverlapBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &Apickup::OverlapEnd);
}

void Apickup::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));
		}
		Pick();
	}
}

void Apickup::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap no"));
		}
		NoPick();
	}
}

// Called every frame
void Apickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

