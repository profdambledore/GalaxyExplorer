// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/MoveablesList.h"
#include "Ship/ShipMoveable.h"

FMoveablesList::FMoveablesList()
{
}

FMoveablesList::FMoveablesList(UShipMoveable* InitialMoveable)
{
	Components.Add(InitialMoveable);
}

FMoveablesList::~FMoveablesList()
{
}
