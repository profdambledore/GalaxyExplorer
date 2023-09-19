// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship/BaseShip.h"

#include "Interactables/Ship/BaseShipInteractable.h"
#include "Ship/Gimbal/VTOLGimbal.h"
#include "Ship/LandingGear.h"
#include "Ship/ShipLight.h"
#include "Ship/ShipMoveable.h"
#include "Interactables/Ship/ShipChair.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	ShipMesh->SetupAttachment(Root, "");
}

// Called when the game starts or when spawned
void ABaseShip::BeginPlay()
{
	Super::BeginPlay();

	// Get all child actor classes, check if they are ship interactables.  If they are, link the pointer
	TArray<AActor*> childActors;
	GetAttachedActors(childActors, true);

	for (int i = 0; i < childActors.Num(); i++) {
		// If the interactable is a ship chair, then add it to the Chairs map and add
		// a new index to the PlayersInSeats map
		if (childActors[i]->IsA(AShipChair::StaticClass())) {
			AShipChair* currentChair = Cast<AShipChair>(childActors[i]);
			currentChair->SetOwningShip(this);
			Chairs.Add(currentChair->InteractableTags, currentChair);
			PlayersInSeats.Add(currentChair->InteractableTags, nullptr);
		}
		else if (childActors[i]->IsA(ABaseShipInteractable::StaticClass())) {
			Interactables.Add(Cast<ABaseShipInteractable>(childActors[i]));
			Interactables[Interactables.Num() - 1]->SetOwningShip(this);
		}
	}

	// Get all VTOL gimbals and add them to the array
	TArray<UActorComponent*> foundGimbals;
	foundGimbals = GetComponentsByClass(UVTOLGimbal::StaticClass());
	for (int i = 0; i < foundGimbals.Num(); i++) {
		VTOLGimbals.Add(Cast<UVTOLGimbal>(foundGimbals[i]));
	}

	// Get all landing gears and add them to the array
	TArray<UActorComponent*> foundLandingGears;
	foundLandingGears = GetComponentsByClass(ULandingGear::StaticClass());
	for (int i = 0; i < foundLandingGears.Num(); i++) {
		LandingGears.Add(Cast<ULandingGear>(foundLandingGears[i]));
	}

	// Get all ship lights and add them to the array
	TArray<UActorComponent*> foundLights;
	foundLights = GetComponentsByClass(ULightComponent::StaticClass());
	for (int i = 0; i < foundLights.Num(); i++) {
		if (foundLights[i]->ComponentHasTag("Exterior")) {
			ExteriorLights.Add(Cast<ULightComponent>(foundLights[i]));
		}
		else if (foundLights[i]->ComponentHasTag("Interior")) {
			InteriorLights.Add(Cast<ULightComponent>(foundLights[i]));
		}
	}

	// Get all ShipMoveables and sort them in the Moveables map based on their tags
	TArray<UActorComponent*> foundMoveables;
	foundMoveables = GetComponentsByClass(UShipMoveable::StaticClass());
	for (int i = 0; i < foundMoveables.Num(); i++) {
		TArray<FName> tags = foundMoveables[i]->ComponentTags;
		for (int j = 0; j < tags.Num(); j++) {
			// Check if index in map exists.  If no, add a new index
			if (Moveables.Contains(tags[j])) {
				Moveables[tags[j]].Components.Add(Cast<UShipMoveable>(foundMoveables[i]));
			}
			else {
				Moveables.Add(tags[j], FMoveablesList(Cast<UShipMoveable>(foundMoveables[i])));
			}
		}
	}

	// Toggle the exterior lights off and landing gear down on spawn
	ToggleExteriorLights();
	ToggleLandingGear();
}

// Called every frame
void ABaseShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseShip::TurnShipOn()
{
}

void ABaseShip::FlightReady()
{
}

void ABaseShip::ToggleLandingGear()
{
	// Flip the bool and toggle all landing gears
	bLandingGearDown = !bLandingGearDown;
	for (int i = 0; i < LandingGears.Num(); i++) {
		LandingGears[i]->ToggleLandingGear(bLandingGearDown);
	}
}

void ABaseShip::ToggleExteriorLights()
{
	// Flip the bool and toggle all exterior lights
	bExLightsOn = !bExLightsOn;
	for (int i = 0; i < ExteriorLights.Num(); i++) {
		ExteriorLights[i]->SetVisibility(bExLightsOn);
	}
}

void ABaseShip::ToggleInteriorLights()
{
	// Flip the bool and toggle all interior lights
	bInLightsOn = !bInLightsOn;
	for (int i = 0; i < InteriorLights.Num(); i++) {
		InteriorLights[i]->SetVisibility(bInLightsOn);
	}
}

void ABaseShip::ToggleVTOLMode()
{
	// Flip the bool and toggle all VTOL gimbals
	bInVTOLMode = !bInVTOLMode;
	for (int i = 0; i < VTOLGimbals.Num(); i++) {
		VTOLGimbals[i]->ToggleVTOLMode(bInVTOLMode);
	}
}

void ABaseShip::ToggleMoveables(FName TagName, bool bIsDoor)
{
	// Check if the inputted tag exists.  If it does, then...
	if (Moveables.Contains(TagName)) {
		// Get all of the moveables of the tag
		FMoveablesList* moveablesToModify = Moveables.Find(TagName);
		if (moveablesToModify) {
			for (int i = 0; i < moveablesToModify->Components.Num(); i++) {
				// If the input stated that the moveable was a door, modify the doorsOpen int
				// and play/reverse the moveable
				if (bIsDoor) {
					doorsOpen += moveablesToModify->Components[i]->ToggleMoveable(1);
				}
				else {
					// Play or reverse the moveable
					moveablesToModify->Components[i]->ToggleMoveable(1);
				}
			}
		}
	}
}

void ABaseShip::CloseAllDoors()
{
	// Collect all moveables which have the Doors tag
	FMoveablesList* moveablesToModify = Moveables.Find("Doors");

	// Set stateToSet to 3, then change it to 2 if one or more doors are open
	int stateToSet = 3;
	if (doorsOpen != 0) {
		stateToSet = 2;
	}

	// Set all doors to the calculated state (3 = open all / 2 = close all) 
	for (int i = 0; i < moveablesToModify->Components.Num(); i++) {
		doorsOpen += moveablesToModify->Components[i]->ToggleMoveable(stateToSet);
	}

	// Reset doorsOpen to 0 if it is less than 0
	// Due to all doors being triggered, even the ones already closed
	if (doorsOpen < 0) {
		doorsOpen = 0;
	}
}