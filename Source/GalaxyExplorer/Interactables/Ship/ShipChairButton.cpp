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

	case 1:
		// Toggle the state of the ships power
		OwningShip->ToggleShipOn();

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 2:
		OwningShip->FlightReady();

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

void AShipChairButton::UpdateButtonEnabled()
{
	if (InteractableTags == "FlightReady") {
		bEnabled = OwningShip->bEnginesOn;
	}
	else if (InteractableTags == "PowerOn") {
		bEnabled = OwningShip->bPoweredOn;
	}
}
