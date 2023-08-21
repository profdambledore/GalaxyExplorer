// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Panel/BasePanel.h"

#include "Components/WidgetComponent.h"

#include "ShipManagerPanel.generated.h"

class ABaseCharacter;

UCLASS()
class GALAXYEXPLORER_API AShipManagerPanel : public ABasePanel
{
	GENERATED_BODY()
	

public:
	AShipManagerPanel();

	virtual void BeginPlay() override;

	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee) override;

	void UpdateManagerWidget(int Index);

	virtual void Interact_Lock(ABaseCharacter* Interactee) override;
	virtual void Interact_OnUnlock(ABaseCharacter* Interactee) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
		class UShipManagerUI* ManagerWidget = nullptr;

public:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* ShipSpawnComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* ManagerWidgetComponent;
};
