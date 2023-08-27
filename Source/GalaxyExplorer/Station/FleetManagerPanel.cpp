// Fill out your copyright notice in the Description page of Project Settings.


#include "Station/FleetManagerPanel.h"

#include "Interactables/BaseInteractable.h"
#include "Station/StationManager.h"
#include "Interactables/Panel/ShipManagerPanel.h"
#include "Interactables/Panel/PanelButton.h"
#include "UI/ShipManagerUI.h"

class UShipManagerUI;

// Sets default values
AFleetManagerPanel::AFleetManagerPanel()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Child Actors
	PanelComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Panel"));
	PanelComponent->SetupAttachment(Root, "");
	PanelComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 76.0f));

	ButtonComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button"));
	ButtonComponent->SetupAttachment(Root, "");

	static ConstructorHelpers::FClassFinder<ABaseInteractable>PanelClass(TEXT("/Game/Interactables/C/BP_ShipManagerPanel"));
	if (PanelClass.Succeeded()) {
		PanelComponent->SetChildActorClass(PanelClass.Class);
	};

	static ConstructorHelpers::FClassFinder<ABaseInteractable>ButtonClass(TEXT("/Game/Interactables/C/BP_PanelButton"));
	if (ButtonClass.Succeeded()) {
		ButtonComponent->SetChildActorClass(ButtonClass.Class);
	};


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFleetManagerPanel::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the classes of the child actors
	Panel = Cast<AShipManagerPanel>(PanelComponent->GetChildActor());
	Button = Cast<APanelButton>(ButtonComponent->GetChildActor());
}

// Called every frame
void AFleetManagerPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStationManager* AFleetManagerPanel::GetOwningStation()
{
	return nullptr;
}