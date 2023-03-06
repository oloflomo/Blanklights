// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InvItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ELOL_API UInvItem : public UObject
{
	GENERATED_BODY()

public:
	UInvItem();

	void Init(FString type, double value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UInventoryComponent* OwningInventory;
};
