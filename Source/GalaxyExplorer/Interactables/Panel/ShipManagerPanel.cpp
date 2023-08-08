// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BaseCharacter.h"
#include "Interactables/Panel/ShipManagerPanel.h"

AShipManagerPanel::AShipManagerPanel() {

	ShipSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Ship Spawn Location"));

}

void AShipManagerPanel::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	if (InteractionValue == 0) {
		Interactee->AttachToInteractable(this);
	}
}