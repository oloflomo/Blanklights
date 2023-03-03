// Fill out your copyright notice in the Description page of Project Settings.


#include "ELOLGameInstance.h"

// Sets default values
UELOLGameInstance::UELOLGameInstance()
{
	//Create components
	LaserCnt = 0;
	RocketCnt = 0;
	BlueLaserCnt = 0;
}

void UELOLGameInstance::RollItem()
{
	UInvItem* NewItem = NewObject<UInvItem>(UInvItem::StaticClass());
	Items.Add(NewItem);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
	}
}