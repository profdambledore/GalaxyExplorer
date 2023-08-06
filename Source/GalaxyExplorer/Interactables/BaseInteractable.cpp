// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BaseInteractable.h"

// Sets default values
ABaseInteractable::ABaseInteractable()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	InteractionWidgetPos = CreateDefaultSubobject<USceneComponent>(TEXT("Interaction Widget Pos"));

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

void ABaseInteractable::Interact(int InteractionValue)
{
	switch (InteractionValue) {
	case 0:
		Interact_Use();
		break;

	default:
		break;
	}

}

void ABaseInteractable::Interact_Use()
{

}

