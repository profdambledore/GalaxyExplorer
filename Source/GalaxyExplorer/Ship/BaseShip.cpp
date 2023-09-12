// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship/BaseShip.h"

#include "Interactables/Ship/BaseShipInteractable.h"
#include "Ship/Gimbal/VTOLGimbal.h"
#include "Ship/LandingGear.h"
#include "Ship/ShipLight.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		if (childActors[i]->IsA(ABaseShipInteractable::StaticClass())) {
			Interactables.Add(Cast<ABaseShipInteractable>(childActors[i]));
			Interactables[i]->SetOwningShip(this);
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
	bLandingGearDown = !bLandingGearDown;
	for (int i = 0; i < LandingGears.Num(); i++) {
		LandingGears[i]->ToggleLandingGear(bLandingGearDown);
	}
}

void ABaseShip::ToggleExteriorLights()
{
	bExLightsOn = !bExLightsOn;
	for (int i = 0; i < ExteriorLights.Num(); i++) {
		ExteriorLights[i]->SetVisibility(bExLightsOn);
	}
}

void ABaseShip::ToggleInteriorLights()
{
	bInLightsOn = !bInLightsOn;
	for (int i = 0; i < InteriorLights.Num(); i++) {
		InteriorLights[i]->SetVisibility(bInLightsOn);
	}
}

void ABaseShip::ToggleVTOLMode()
{
	bInVTOLMode = !bInVTOLMode;
	for (int i = 0; i < VTOLGimbals.Num(); i++) {
		VTOLGimbals[i]->ToggleVTOLMode(bInVTOLMode);
	}
}

