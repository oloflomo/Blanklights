// Fill out your copyright notice in the Description page of Project Settings.


#include "InvItem.h"

UInvItem::UInvItem()
{
	type = "";
	value = 0;
}

void UInvItem::Init(FString T, double V)
{
	type = T;
	value = V;
}

