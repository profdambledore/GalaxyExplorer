// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Panel/ShipManagerPanel.h"

#include "Player/BaseCharacter.h"
#include "UI/ShipManagerUI.h"

AShipManagerPanel::AShipManagerPanel() {

	ShipSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Ship Spawn Location"));

	ManagerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget Component"));
	ManagerWidgetComponent->SetupAttachment(Root, "");

	// Find InteractWidget object and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Interactables/UI/WBP_FleetManager"));
	if (UIClass.Succeeded()) {
		ManagerWidgetComponent->SetWidgetClass(UIClass.Class);
	};
}

void AShipManagerPanel::BeginPlay() {

	Super::BeginPlay();

	// Get reference to the interact widget class
	ManagerWidget = Cast<UShipManagerUI>(ManagerWidgetComponent->GetWidget());
}

void AShipManagerPanel::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	if (InteractionValue == 0) {
		Interact_Lock(Interactee);
	}
}

void AShipManagerPanel::UpdateManagerWidget(int Index)
{
	ManagerWidget->UpdateManagerSwitcher(Index);
}

void AShipManagerPanel::Interact_Lock(ABaseCharacter* Interactee)
{
	Interactee->AttachToInteractable(this);
	ManagerWidget->UpdateFleetList(Interactee);
	UpdateManagerWidget(1);
}

void AShipManagerPanel::Interact_OnUnlock(ABaseCharacter* Interactee)
{
	ManagerWidget->ClearFleetList();
	UpdateManagerWidget(0);
}
