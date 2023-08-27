// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ShipManagerUI.h"

#include "Station/StationManager.h"
#include "Player/BaseCharacter.h"


void UShipManagerUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UShipManagerUI::UpdateStationDetails(FString InName, AStationManager* InPointer)
{
	StationName->SetText(FText::FromString(InName));
	OwningStation = InPointer;
}

void UShipManagerUI::ClearFleetList()
{
	FleetList->ClearListItems();
	CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
}

void UShipManagerUI::UpdateManagerSwitcher(int Index)
{
	ManagerSwitcher->SetActiveWidgetIndex(Index);
}

