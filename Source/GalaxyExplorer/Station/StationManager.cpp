// Fill out your copyright notice in the Description page of Project Settings.


#include "Station/StationManager.h"

#include "Station/StationSpawnLocation.h"
#include "Station/FleetManagerPanel.h"
#include "Interactables/Panel/ShipManagerPanel.h"
#include "UI/ShipManagerUI.h"

// Sets default values
AStationManager::AStationManager()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStationManager::BeginPlay()
{
	Super::BeginPlay();

	// Update all SpawnLocations station pointers to this
	for (int i = 0; i < SpawnLocations.Num(); i++) {
		SpawnLocations[i]->Station = this;
	}

	// Update all FleetManagers station pointers to this
	for (int i = 0; i < FleetManagers.Num(); i++) {
		FleetManagers[i]->Station = this;
		FleetManagers[i]->Panel->ManagerWidget->UpdateStationDetails(StationName, this);
	}	
}

// Called every frame
void AStationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStationSpawnLocation* AStationManager::GetSuitableSpawnLocation(TEnumAsByte<EShipClassification> InClass)
{
	for (int i = 0; i < SpawnLocations.Num(); i++) {
		if (SpawnLocations[i]->ReturnPadData().GetValue() <= InClass.GetValue() && SpawnLocations[i]->PadNotInUse()) {
			return SpawnLocations[i];
		}
	}
	return nullptr;
}

FString AStationManager::SpawnShip(FShipData InShipData)
{
	// First, search through the spawn locations array to find a suitable spawn location
	// If one isn't found, then return false
	AStationSpawnLocation* FoundSpawnLocation = GetSuitableSpawnLocation(InShipData.Classification);
	if (!FoundSpawnLocation) {
		return "x";
	}
	FoundSpawnLocation->SpawnShipAtLocation(InShipData);
	return FoundSpawnLocation->SpawnLocationName;
}


