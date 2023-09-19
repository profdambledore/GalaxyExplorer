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

	case 4:
		// Toggle state of a tag name
		OwningShip->ToggleMoveables(InteractableTags, true);
		if (OwningShip->doorsOpen != 0) {
			bEnabled = true;
		}
		else {
			bEnabled = false;
		}

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 5:
		// Close all doors if one or more is open, else open all doors
		OwningShip->CloseAllDoors();
		if (OwningShip->doorsOpen != 0) {
			bEnabled = true;
			UE_LOG(LogTemp, Warning, TEXT("TRUE"));
		}
		else {
			bEnabled = false;
			UE_LOG(LogTemp, Warning, TEXT("FALSE"));
		}
		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	default:
		break;
	}
}

void ABaseShipInteractable::OnCasted()
{
	if (InterationPointsPowerOff.Num() != 0) {
		if (OwningShip->doorsOpen != 0) {
			bEnabled = true;
			UE_LOG(LogTemp, Warning, TEXT("TRUE"));
		}
		else {
			bEnabled = false;
			UE_LOG(LogTemp, Warning, TEXT("FALSE"));
		}
	}
}
