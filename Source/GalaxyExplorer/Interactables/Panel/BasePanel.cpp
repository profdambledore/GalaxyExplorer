// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Panel/BasePanel.h"

void ABasePanel::Interact(int InteractionValue, ABaseCharacter* Interactee)
{

	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel Mesh"));

	PanelWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Panel Widget Component"));
	PanelWidgetComponent->SetupAttachment(PanelMesh, "");
}