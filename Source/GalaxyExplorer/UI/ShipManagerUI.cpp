// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BaseCharacter.h"
#include "UI/ShipManagerUI.h"

void UShipManagerUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UShipManagerUI::ClearFleetList()
{
	FleetList->ClearListItems();
	CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
}

void UShipManagerUI::UpdateManagerSwitcher(int Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Widget to"));
	ManagerSwitcher->SetActiveWidgetIndex(Index);
}
