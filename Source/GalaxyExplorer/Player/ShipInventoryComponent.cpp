// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShipInventoryComponent.h"

// Sets default values for this component's properties
UShipInventoryComponent::UShipInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShipInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	FShipData TestShip(FString("Test Ship"), EShipManufacturer::Focalors, NULL, FString("In Storage"), FString("Doreville"), 0, 3, 1 );
	AddShipToList(TestShip);
	// ...
	
}


// Called every frame
void UShipInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FShipData> UShipInventoryComponent::GetPlayerShipList()
{
	return PlayerShipList;
}

void UShipInventoryComponent::AddShipToList(FShipData NewShip)
{
	PlayerShipList.Add(NewShip);
}

