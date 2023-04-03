// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InvItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ELOL_API UInvItem : public UObject
{
	GENERATED_BODY()

public:
	UInvItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		class UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FText UseActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
		float Weight;

	UPROPERTY()
		class UInventoryComponent* OwningInventory;

	virtual void Use(class APlayerShipBase* PlayerShip) PURE_VIRTUAL(UInvItem, );

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class APlayerShipBase* PlayerShip);

};
