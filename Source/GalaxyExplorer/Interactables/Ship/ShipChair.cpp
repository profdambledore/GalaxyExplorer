// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactables/Ship/ShipChair.h"

#include "Ship/BaseShip.h"
#include "Player/BaseCharacter.h"
#include "Interactables/Ship/ShipChairButton.h"
#include "Data/ShipChairData.h"

AShipChair::AShipChair() 
{
	// Setup the chairs components
	SeatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seat Mesh"));

	PlayerAttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Player Attachment Point"));
	PlayerAttachmentPoint->SetupAttachment(Root, "");

	PlayerEjectionPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Player Ejection Point"));
	PlayerEjectionPoint->SetupAttachment(Root, "");
}

void AShipChair::BeginPlay()
{
	Super::BeginPlay();

	// Get all child actor classes, check if they are ship interactables.  If they are, link the pointer
	TArray<AActor*> childActors;
	GetAttachedActors(childActors, true);

	// Get and store all child actor buttons in the array
	for (int i = 0; i < childActors.Num(); i++) {
		if (childActors[i]->IsA(AShipChairButton::StaticClass())) {
			AShipChairButton* newButton = Cast<AShipChairButton>(childActors[i]);
			Buttons.Add(newButton);

			// Then update their properties
			newButton->LinkedChair = this;
			newButton->SetOwningShip(OwningShip);
			newButton->InteractableTags = InteractableTags;
		}
	}
}

void AShipChair::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	int chairIndex;
	switch (InteractionValue) {
	case 0:
		// Toggle the state of the chairs moveable (if it has one)
		OwningShip->ToggleMoveables(InteractableTags, false);
		bEnabled = true;
		Buttons[0]->bEnabled = true;

		// Update the ships pointer to use the interactee
		chairIndex = OwningShip->FindSeat(InteractableTags);
		if (chairIndex != -1) {
			OwningShip->Chairs[chairIndex].Player = Interactee;
		}

		// Remove Interactee collision and attach the interactee to the seat
		//Interactee->SetActorEnableCollision(false);
		Interactee->SetActorLocation(PlayerAttachmentPoint->GetComponentLocation(), false, NULL, ETeleportType::TeleportPhysics);
		Interactee->AttachToSeat(true, OwningShip);

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	case 1:
		// Detach from the chair
		// Toggle the state of the chairs moveable (if it has one)
		OwningShip->ToggleMoveables(InteractableTags, false);
		bEnabled = false;
		Buttons[0]->bEnabled = false;

		// Remove Interactee collision and attach the interactee to the seat
		//Interactee->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Interactee->SetActorLocation(PlayerEjectionPoint->GetComponentLocation(), false, NULL, ETeleportType::TeleportPhysics);
		Interactee->AttachToSeat(false, OwningShip);

		// Update the ships pointer to use the interactee
		chairIndex = OwningShip->FindSeat(InteractableTags);
		if (chairIndex != -1) {
			OwningShip->Chairs[chairIndex].Player = nullptr;
		}

		// Then update the Interactees interaction widget
		Interactee->UpdateInteractWidget();
		break;

	default:
		break;
	}
}

void AShipChair::OnCasted()
{
	
}

void AShipChair::UpdateButtons()
{
	for (int i = 0; i < Buttons.Num(); i++) {
		Buttons[i]->UpdateButtonEnabled();
	}
}
