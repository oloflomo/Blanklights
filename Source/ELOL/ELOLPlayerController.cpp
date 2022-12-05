// Fill out your copyright notice in the Description page of Project Settings.


#include "ELOLPlayerController.h"

void AELOLPlayerController::thrusting(bool sth)
{
	// Change the value of the bSomeBool property
	thru = true;
	// If this next check succeeds, we are *not* the authority, meaning we are a network client.
	// In this case we also want to call the server function to tell it to change the bSomeBool property as well.
	//if (Role < ROLE_Authority)
	//{
	//	Serverthrusting(sth);
	//}
}

//server

bool AELOLPlayerController::Serverthrusting_Validate(bool sth)
{
	return true;
}

void AELOLPlayerController::Serverthrusting_Implementation(bool sth)
{
	thrusting(sth);
}
