// Fill out your copyright notice in the Description page of Project Settings.


#include "InvItem.h"

UInvItem::UInvItem()
{
	Weight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

