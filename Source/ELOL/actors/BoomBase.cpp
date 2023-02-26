// Fill out your copyright notice in the Description page of Project Settings.


#include "BoomBase.h"

// Sets default values
ABoomBase::ABoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_A.P_Explosion_Big_A'"));
	ParticleFX1 = Particle.Object;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetRelativeLocation(FVector(0, 0, 0));
	Root->SetWorldRotation(FRotator(0, 0, 0));

	RootComponent = Root;
}

// Called when the game starts or when spawned
void ABoomBase::BeginPlay()
{
	Super::BeginPlay();
	lifespan = 10;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX1, Root->GetComponentLocation());
}

// Called every frame
void ABoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	lifespan--;
	if (lifespan < 0)
	{
		GetWorld()->DestroyActor(this);
	}
}

