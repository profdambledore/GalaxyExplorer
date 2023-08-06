// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameplayTagContainer.h"

#include "BaseInteractable.generated.h"

UCLASS()
class GALAXYEXPLORER_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Interact(int InteractionValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Use();

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* InteractionWidgetPos;


	// How the player can interact with the interactable
	// int - the value associated with the interation (eg: use = 0, turn on = 1)
	// FString - the display name of the interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		TMap<int, FString> InterationPoints;

	// Gameplay Tag Container
	FGameplayTagContainer TagContainer;

};
