// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Ship/BaseShipInteractable.h"
#include "ShipChairButton.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYEXPLORER_API AShipChairButton : public ABaseShipInteractable
{
	GENERATED_BODY()
	
public:
	// Overriden Inherited functions from ABaseShipInteractable
	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);
	virtual void OnCasted();

	void UpdateButtonEnabled();


public:
	// Pointer to the chair this button is attached too
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AShipChair* LinkedChair = nullptr;
};
