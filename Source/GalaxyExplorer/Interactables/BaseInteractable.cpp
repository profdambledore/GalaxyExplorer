// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/BaseInteractable.h"

#include "Player/BaseCharacter.h"

// Sets default values
ABaseInteractable::ABaseInteractable()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	InteractionWidgetPos = CreateDefaultSubobject<USceneComponent>(TEXT("Interaction Widget Pos"));
	InteractionWidgetPos->SetupAttachment(Root, "");

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Interactable")));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInteractable::Interact(int InteractionValue, ABaseCharacter* Interactee)
{
	switch (InteractionValue) {
	case -1:
		UE_LOG(LogTemp, Warning, TEXT("Turn On"));
		Interact_TurnOn(Interactee);
		break;

	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Case 0"));
		Interact_Lock(Interactee);
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Defaulted"));
		break;
	}

}

void ABaseInteractable::Interact_Lock(ABaseCharacter* Interactee)
{
	Interactee->AttachToInteractable(this);
}

void ABaseInteractable::Interact_TurnOn(ABaseCharacter* Interactee)
{
	// Toggle the bool from false to true
	bPowerOn = true;

	// Then update the Interactees interaction widget
	Interactee->UpdateInteractWidget();
}

void ABaseInteractable::Interact_OnUnlock(ABaseCharacter* Interactee)
{
}

