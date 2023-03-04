// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipBase.h"

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

	RootComponent = Root;
}

// Player actions

void APlayerShipBase::thrusting(float timedelta)
{
	FVector XUnit = Root->GetRelativeRotation().Vector();
	Root->AddForce(100000 * timedelta * XUnit);
	//Controller.thrusting(1);
}

void APlayerShipBase::yawing(float timedelta)
{
	FVector YUnit = Root->GetRightVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(1000000, 0, 0));
}

void APlayerShipBase::pitching(float timedelta)
{
	FVector ZUnit = Root->GetUpVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 0, 1), FVector(1000000, 0, 0));
}

void APlayerShipBase::rolling(float timedelta)
{
	FVector ZUnit = Root->GetUpVector();
	Root->AddForceAtLocationLocal(timedelta * FVector(0, 1, 0), FVector(0, 0, 1000000));
}

void APlayerShipBase::InitFire()
{
	GetWorld()->SpawnActor<AActor>(BulletType, GetActorLocation() + FVector(500, -50, 0), GetActorRotation());
	GetWorld()->SpawnActor<AActor>(BulletType, GetActorLocation() + FVector(500, 50, 0), GetActorRotation());
}

void APlayerShipBase::ShowInv()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	InvWidget->AddToViewport();
}

void APlayerShipBase::HideInv()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	InvWidget->RemoveFromViewport();
}

void APlayerShipBase::ShowLoot()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	UELOLGameInstance* GameInst = Cast<UELOLGameInstance>(GetGameInstance());

	GameInst->RollItem();
	GameInst->RollItem();
	GameInst->RollItem();

	LootWidget->AddToViewport();
}

void APlayerShipBase::HideLoot()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	LootWidget->RemoveFromViewport();
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
	UProgressBar* ProgressBar = dynamic_cast<UProgressBar*>(Widget->GetWidgetFromName(FName("ProgressBar_60")));
	ProgressBar->SetPercent(durability / double(101));
}

void APlayerShipBase::Destruction()
{
	GetWorld()->SpawnActor<AActor>(BoomType, GetActorLocation(), GetActorRotation());
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

//overrides
void APlayerShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (durability < 0)
	{
		Destruction();
	}
}

void APlayerShipBase::BeginPlay()
{
	Super::BeginPlay();
	durability = 100;
	Root->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);
	Mesh2->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);
	Mesh3->OnComponentHit.AddDynamic(this, &APlayerShipBase::OnHit);

	Widget = CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass);

	InvWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), InvWidgetClass);

	LootWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), LootWidgetClass);

	Widget->AddToViewport();
}




// Called to bind functionality to input
void APlayerShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//register inputs
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShipBase::ServerInitFire);
	PlayerInputComponent->BindAction("Inv", IE_Pressed, this, &APlayerShipBase::ShowInv);
	PlayerInputComponent->BindAction("Inv", IE_Released, this, &APlayerShipBase::HideInv);
	PlayerInputComponent->BindAxis("thrust", this, &APlayerShipBase::Serverthrusting);
	PlayerInputComponent->BindAxis("pitch", this, &APlayerShipBase::Serverpitching);
	PlayerInputComponent->BindAxis("yaw", this, &APlayerShipBase::Serveryawing);
	PlayerInputComponent->BindAxis("roll", this, &APlayerShipBase::Serverrolling);
}

/*UnrealEditor_UMG
UnrealEditor_ELOL!APlayerShipBase::Collision() [C:\Users\strza\Desktop\electronics moba data\project files\game\Source\ELOL\pawns\PlayerShipBase.cpp:174]
UnrealEditor_ELOL!ARocket::Collision() [C:\Users\strza\Desktop\electronics moba data\project files\game\Source\ELOL\actors\Rocket.cpp:44]
UnrealEditor_ELOL!ARocket::OnHit() [C:\Users\strza\Desktop\electronics moba data\project files\game\Source\ELOL\actors\Rocket.cpp:66]
UnrealEditor_ELOL!ARocket::execOnHit() [C:\Users\strza\Desktop\electronics moba data\project files\game\Intermediate\Build\Win64\UnrealEditor\Inc\ELOL\UHT\Rocket.gen.cpp:37]
UnrealEditor_CoreUObject*/