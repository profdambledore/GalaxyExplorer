// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameplayTagContainer.h"

#include "BaseInteractable.generated.h"

class ABaseCharacter;

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
		virtual void Interact(int InteractionValue, ABaseCharacter* Interactee);

	virtual void Interact_Lock(ABaseCharacter* Interactee);
	virtual void Interact_OnUnlock(ABaseCharacter* Interactee);
	virtual void OnCasted();

	void SetEnabled(bool bNewEnabled);
	void SetRecievePower(bool bNewRecievePower);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* InteractionWidgetPos;

	// Bool to denote if the player can lock to the interactable, currently unused
	bool bLockPlayerToInteractable = false;

	// How the player can interact with the interactable if it is turned on
	// int - the value associated with the interation (eg: use = 0, turn on = 1)
	// FString - the display name of the interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		TMap<int, FString> InterationPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		TMap<int, FString> InterationPointsPowerOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Widget")
		FRotator WidgetRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Widget")
		FVector WidgetScale = FVector(1.0f, 1.0f, 1.0f);

	// -- Power
	// Bool to denote if the interactable is recieving power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
		bool bRecievingPower = true;

	// Bool to denote if the interactable is enabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
		bool bEnabled = true;

	// Bool to denote if interactable should be treated as always recieveing power.
	// Some interactables (such as buttons) should always be able to be used 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
		bool bIgnorePower = true;

	// Gameplay Tag Container
	FGameplayTagContainer TagContainer;

};
