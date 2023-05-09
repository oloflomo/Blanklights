// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipBase.h"
#include "Components/Button.h"

APlayerShipBase::APlayerShipBase()
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

	Root->SetStaticMesh(Asset1);
	Root->SetSimulatePhysics(true);
	Root->SetEnableGravity(0);


	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(Root);
	Mesh2->SetStaticMesh(Asset2);
	Mesh2->SetRelativeLocation(FVector(0, 0, 0));
	Mesh2->SetWorldRotation(FRotator(0, 0, 0));
	Mesh2->SetSimulatePhysics(false);

	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Mesh3->SetupAttachment(Root);
	Mesh3->SetStaticMesh(Asset3);
	Mesh3->SetRelativeLocation(FVector(0, 0, 0));
	Mesh3->SetWorldRotation(FRotator(0, 0, 0));
	Mesh3->SetSimulatePhysics(false);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	/*Way_comp = CreateDefaultSubobject<UWaypointComponent>(TEXT("Wid_comp"));

	Way_comp->SetupAttachment(Root);
	Way_comp->SetRelativeLocation(FVector(0, 0, 0));
	Way_comp->SetWorldRotation(FRotator(0, 0, 0));*/

	EngineType = 0;

	RootComponent = Root;
}

// Player actions

void APlayerShipBase::thrusting(float timedelta)
{
	FVector XUnit = Root->GetRelativeRotation().Vector();
	if (!EngineType)
	{
		Root->AddForce(1000000 * timedelta * XUnit);
	}
	//Controller.thrusting(1);
}

void APlayerShipBase::yawing(float timedelta)
{
	FVector YUnit = Root->GetRightVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(10000000, 0, 0));
}

void APlayerShipBase::pitching(float timedelta)
{
	FVector ZUnit = Root->GetUpVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 0, 1), FVector(10000000, 0, 0));
}

void APlayerShipBase::rolling(float timedelta)
{
	FVector ZUnit = Root->GetUpVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(0, 0, 10000000));
}

void APlayerShipBase::InitFire()
{
	if (BulletType && AmmoLeft)
	{
		FVector FUnit = Root->GetForwardVector();
		FVector TUnit = Root->GetRightVector();
		FTransform SpawnTransform1 = FTransform(GetActorRotation(), GetActorLocation() + 300 * FUnit + 40 * TUnit, FVector(1, 1, 1));
		FTransform SpawnTransform2 = FTransform(GetActorRotation(), GetActorLocation() + 300 * FUnit - 40 * TUnit, FVector(1, 1, 1));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		GetWorld()->SpawnActor<AActor>(BulletType, SpawnTransform1, SpawnParameters);
		GetWorld()->SpawnActor<AActor>(BulletType, SpawnTransform2, SpawnParameters);
		AmmoLeft--;
	}
}

void APlayerShipBase::SwapEngine()
{
	EngineType = !EngineType;
	warp_vec = Root->GetComponentRotation().Vector();
	if (!EngineType)
	{
		Root->SetPhysicsLinearVelocity(warp_vec);
		//Root->SetWorldRotation(warp_vec.Rotation());
	}
}

UInvItem* APlayerShipBase::RollItem()
{
	UInvItem* Item = NewObject<UInvItem>(this, ItemClass1);
	return Item;
}

void APlayerShipBase::ShowLoot(UInventoryComponent* ForeignInventory)
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	Inventory->RollItem();

	ShowForeignInv(ForeignInventory);

	if (Widget)
	{
		UButton* Button = dynamic_cast<UButton*>(Widget->GetWidgetFromName(FName("LootButton")));
		if (Button)
		{
			Button->SetVisibility(ESlateVisibility::Visible);
		}
	}

	FuelLeft += 10;
}

void APlayerShipBase::HideLoot()
{
	if (Widget)
	{
		UButton* Button = dynamic_cast<UButton*>(Widget->GetWidgetFromName(FName("LootButton")));
		if (Button)
		{
			Button->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

//server


void APlayerShipBase::Serverthrusting_Implementation(float timedelta)
{
	thrusting(timedelta);
}
bool APlayerShipBase::Serverthrusting_Validate(float timedelta)
{
	return true;
}

void APlayerShipBase::ServerInitFire_Implementation()
{
	InitFire();
}
bool APlayerShipBase::ServerInitFire_Validate()
{
	return true;
}

void APlayerShipBase::Serverpitching_Implementation(float timedelta)
{
	pitching(timedelta);
}
bool APlayerShipBase::Serverpitching_Validate(float timedelta)
{
	return true;
}

void APlayerShipBase::Serveryawing_Implementation(float timedelta)
{
	yawing(timedelta);
}
bool APlayerShipBase::Serveryawing_Validate(float timedelta)
{
	return true;
}

void APlayerShipBase::Serverrolling_Implementation(float timedelta)
{
	rolling(timedelta);
}
bool APlayerShipBase::Serverrolling_Validate(float timedelta)
{
	return true;
}

//events

void APlayerShipBase::Collision(double dmg = 1)
{
	durability -= dmg;
}

void APlayerShipBase::Destruction()
{
	if (BoomType)
	{
		GetWorld()->SpawnActor<AActor>(BoomType, GetActorLocation(), GetActorRotation());
	}
	GetWorld()->DestroyActor(this);
}

void APlayerShipBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

void APlayerShipBase::UseItem(class UInvItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this);
	}
}

//overrides
void APlayerShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (durability < 0)
	{
		Destruction();
	}

	if (EngineType)
	{
		Root->SetPhysicsLinearVelocity(100000 * warp_vec);
		Root->SetWorldRotation(warp_vec.Rotation());
	}

	if (Widget)
	{
		UProgressBar* ProgressBar = dynamic_cast<UProgressBar*>(Widget->GetWidgetFromName(FName("ProgressBar_60")));
		if (ProgressBar)
		{
			ProgressBar->SetPercent(durability / double(100));
		}
	}
}

void APlayerShipBase::BeginPlay()
{
	Super::BeginPlay();
	durability = 100;
	AmmoLeft = 5;
	FuelLeft = 5;
	Root->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);
	Mesh2->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);
	Mesh3->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);

	if (WidgetClass)
	{
		Widget = CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass);
		Widget->AddToViewport();
	}

	Inventory->ItemClass1 = ItemClass1;
}




// Called to bind functionality to input
void APlayerShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShipBase::ServerInitFire);
	PlayerInputComponent->BindAxis("thrust", this, &APlayerShipBase::Serverthrusting);
	PlayerInputComponent->BindAxis("pitch", this, &APlayerShipBase::Serverpitching);
	PlayerInputComponent->BindAxis("yaw", this, &APlayerShipBase::Serveryawing);
	PlayerInputComponent->BindAxis("roll", this, &APlayerShipBase::Serverrolling);
	PlayerInputComponent->BindAction("EngineToggle", IE_Pressed, this, &APlayerShipBase::SwapEngine);
}