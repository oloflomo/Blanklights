// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::RollItem()
{
	//UAmmoInvItem* Item = NewObject<UAmmoInvItem>(UAmmoInvItem::StaticClass());
	UInvItem* Item = NewObject<UInvItem>(UInvItem::StaticClass());
	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AAAAAAA"));
	}

	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::AddItem(UInvItem* Item)
{
	if (!Item)
	{
		return;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::RemoveItem(UInvItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	RollItem();
	RollItem();
	RollItem();
}