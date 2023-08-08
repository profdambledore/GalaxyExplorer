// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Panel/BasePanel.h"
#include "ShipManagerPanel.generated.h"

class ABaseCharacter;

UCLASS()
class GALAXYEXPLORER_API AShipManagerPanel : public ABasePanel
{
	GENERATED_BODY()
	

public:
	AShipManagerPanel();

	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);

public:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* ShipSpawnLocation = nullptr;
};
