// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Panel/PanelButton.h"
#include "Player/BaseCharacter.h"

void APanelButton::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	switch (InteractionValue) {
	case 0:
		// Turn on linked interactables
		for (int i = 0; i < LinkedInteractables.Num(); i++) {
			LinkedInteractables[i]->SetEnabled(true);
		}
		bEnabled = true;

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 1:
		// Turn off
		for (int i = 0; i < LinkedInteractables.Num(); i++) {
			LinkedInteractables[i]->SetEnabled(false);
		}
		bEnabled = false;

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	default:
		break;
	}
}