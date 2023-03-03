// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ELOLGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ELOL_API UELOLGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UELOLGameInstance();

	//variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		double LaserCnt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		double RocketCnt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		double BlueLaserCnt;
};
