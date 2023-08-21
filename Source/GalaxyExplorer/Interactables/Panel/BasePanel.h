// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/BaseInteractable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "BasePanel.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYEXPLORER_API ABasePanel : public ABaseInteractable
{
	GENERATED_BODY()
	

public:
	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);

public:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* PanelMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* PanelWidgetComponent;
};
