// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship/BaseShip.h"

#include "Interactables/Ship/BaseShipInteractable.h"
#include "Ship/Gimbal/VTOLGimbal.h"
#include "Ship/LandingGear.h"

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
			Cast<ABaseShipInteractable>(childActors[i])->SetOwningShip(this);
		}
	}
	
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

