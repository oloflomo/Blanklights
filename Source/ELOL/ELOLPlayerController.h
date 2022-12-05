// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ELOLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ELOL_API AELOLPlayerController : public APlayerController
{
	GENERATED_BODY()
<<<<<<< HEAD

	bool thru;

	void thrusting(bool sth);

	UFUNCTION(reliable, server, WithValidation)
	void Serverthrusting(bool sth);
=======
	
>>>>>>> multiplayer
};
