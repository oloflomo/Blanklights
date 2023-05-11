// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InvItem.h"
#include "AmmoInvItem.generated.h"

/**
 * 
 */

UCLASS()
class ELOL_API UAmmoInvItem : public UInvItem
{
	GENERATED_BODY()

protected:
	virtual void Use(class APlayerShipBase* PlayerShip) override;


public:
	UAmmoInvItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		float Heal;
};
