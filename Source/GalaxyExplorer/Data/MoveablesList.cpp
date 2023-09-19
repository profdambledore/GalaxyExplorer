// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/MoveablesList.h"
#include "Ship/ShipMoveable.h"

// Default constructor
FMoveablesList::FMoveablesList()
{
}

// Constructor where a UShipMoveable can be inputted on construction
FMoveablesList::FMoveablesList(UShipMoveable* InitialMoveable)
{
	Components.Add(InitialMoveable);
}

// Default destructor
FMoveablesList::~FMoveablesList()
{
}
