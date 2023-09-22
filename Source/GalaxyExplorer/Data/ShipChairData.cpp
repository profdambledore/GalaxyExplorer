// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/ShipChairData.h"

#include "Interactables/Ship/ShipChairButton.h"
#include "Player/BaseCharacter.h"

FShipChairData::FShipChairData()
{
}

FShipChairData::FShipChairData(FName NewName, AShipChair* NewChair)
{
	Name = NewName;
	Chair = NewChair;
}

FShipChairData::~FShipChairData()
{
}
