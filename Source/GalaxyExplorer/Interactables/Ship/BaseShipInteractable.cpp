// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Ship/BaseShipInteractable.h"

#include "Ship/BaseShip.h"

void ABaseShipInteractable::SetOwningShip(class ABaseShip* InShip) {
	OwningShip = InShip;
}