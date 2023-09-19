// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Ship/ShipChairButton.h"

#include "Ship/BaseShip.h"
#include "Player/BaseCharacter.h"
#include "Interactables/Ship/ShipChair.h"

void AShipChairButton::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	switch (InteractionValue) {
	case 0:
		// Toggle the state of the chairs moveable (if it has one)
		LinkedChair->Interact(1, Interactee);
		bEnabled = false;
		LinkedChair->bEnabled = false;

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	default:
		break;
	}
}

void AShipChairButton::OnCasted()
{

}