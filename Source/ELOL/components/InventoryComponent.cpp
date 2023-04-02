// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
}

void UInventoryComponent::RollItem()
{
	UInvItem* NewItem = NewObject<UInvItem>(UInvItem::StaticClass());
	NewItem->OwningInventory = this;
	Items.Add(NewItem);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AAAAAAA"));
	}
	OnInventoryUpdated.Broadcast();
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	RollItem();
	RollItem();
	RollItem();
}