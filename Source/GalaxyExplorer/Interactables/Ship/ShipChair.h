// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Ship/BaseShipInteractable.h"

#include "Components/StaticMeshComponent.h"

#include "ShipChair.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYEXPLORER_API AShipChair : public ABaseShipInteractable
{
	GENERATED_BODY()
	

public:
	AShipChair();

	virtual void BeginPlay() override;

	// Overriden Inherited functions from ABaseShipInteractable
	virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);
	virtual void OnCasted();

	void UpdateButtons();

public:
	/// -- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* SeatMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* PlayerAttachmentPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* PlayerEjectionPoint;

	/// -- Seated Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seated Player")
		class ABaseCharacter* PlayerInSeat = nullptr;

	/// -- Buttons on the seat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class AShipChairButton*> Buttons;
};
