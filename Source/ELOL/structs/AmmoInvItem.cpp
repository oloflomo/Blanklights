// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoInvItem.h"

void UAmmoInvItem::Use(class APlayerShipBase* PlayerShip)
{
	if (PlayerShip)
	{
		PlayerShip->durability -= Heal;
	}
}

