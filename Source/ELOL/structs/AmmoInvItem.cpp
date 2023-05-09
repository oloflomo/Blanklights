// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoInvItem.h"
#include "ELOL/pawns/PlayerShipBase.h"

UAmmoInvItem::UAmmoInvItem()
{
	Heal = 20.f;
}

void UAmmoInvItem::Use(class APlayerShipBase* PlayerShip)
{
	if (PlayerShip)
	{
		PlayerShip->AmmoLeft += Heal;
	}
}