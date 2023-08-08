// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/BaseInteractable.h"
#include "PanelButton.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYEXPLORER_API APanelButton : public ABaseInteractable
{
	GENERATED_BODY()
	
public:
	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Properties")
		TArray<class ABaseInteractable*>LinkedInteractables;
};
