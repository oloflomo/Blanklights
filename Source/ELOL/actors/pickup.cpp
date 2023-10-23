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
	
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	RootComponent = Mesh;
}

void Apickup::Pick(AActor* other)
{
	//pick
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerShipClass, FoundActors);
	//for (AActor* i : FoundActors) {
	if (other->IsA(APlayerShipBase::StaticClass()))
	{
//		APlayerShipBase* Ship = Cast<APlayerShipBase>(other);		//get player controller	-> show loot (in player controler through hud)
//		Ship->ShowLoot(Inventory);
	}
}

void Apickup::NoPick(AActor* other)
{
	//nopick
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerShipClass, FoundActors);
	//for (AActor* i : FoundActors) {
	if (other->IsA(APlayerShipBase::StaticClass()))
	{
//		APlayerShipBase* Ship = Cast<APlayerShipBase>(other);			//get player controller	-> show loot (in player controler through hud)
//		Ship->HideLoot();
	}
}

// Called when the game starts or when spawned
void Apickup::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &Apickup::OverlapBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &Apickup::OverlapEnd);
	Inventory->ItemClass1 = ItemClass1;

	Inventory->RollItem();
	Inventory->RollItem();
	Inventory->RollItem();
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
		Pick(OtherActor);
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
		NoPick(OtherActor);
	}
}

// Called every frame
void Apickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

