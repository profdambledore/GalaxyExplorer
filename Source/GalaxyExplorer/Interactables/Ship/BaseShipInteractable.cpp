// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Ship/BaseShipInteractable.h"

#include "Ship/BaseShip.h"
#include "Player/BaseCharacter.h"

void ABaseShipInteractable::SetOwningShip(class ABaseShip* InShip) {
	OwningShip = InShip;
}

void ABaseShipInteractable::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	switch (InteractionValue) {
	case 0:
		// Toggle state of exterior ship light
		OwningShip->ToggleExteriorLights();

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 1:
		// Toggle state of ship landing gear
		OwningShip->ToggleInteriorLights();

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 2:
		// Toggle state of ship VTOL mode
		OwningShip->ToggleVTOLMode();

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 3:
		// Toggle state of ship landing gear
		OwningShip->ToggleLandingGear();

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	default:
		break;
	}
}