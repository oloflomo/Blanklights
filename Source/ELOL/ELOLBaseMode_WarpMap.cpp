// Fill out your copyright notice in the Description page of Project Settings.


#include "ELOLBaseMode_WarpMap.h"
#include "Bop.h"
#include "PlayerShip.h"

AELOLBaseMode_WarpMap::AELOLBaseMode_WarpMap()
{
	DefaultPawnClass = APlayerShip::StaticClass();
}