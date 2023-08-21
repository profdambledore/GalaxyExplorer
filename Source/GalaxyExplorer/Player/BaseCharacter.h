// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Unreal Includes
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetInteractionComponent.h"

#include "BaseCharacter.generated.h"

UCLASS()
class GALAXYEXPLORER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttachToInteractable(AActor* ActorToAttachTo);
	void UpdateInteractWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Axis
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void CameraX(float AxisValue);
	void CameraY(float AxisValue);
	void FocusCamera(float AxisValue);
	void ZoomThirdPersonCamera(float AxisValue);

	// Action
	void InteractModePress();
	void InteractModeRelease();
	void InteractModePrimaryPress();
	void InteractModePrimaryRelease();
	void ToggleCameraMode();

	void JumpPress();
	void JumpRelease();

	/// -- Interact
	void QuickInteract();

public:	
	/// -- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
		APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
		class UInteractWidget* InteractWidget = nullptr;

	/// -- Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* PlayerCameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* InteractWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetInteractionComponent* WidgetInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UShipInventoryComponent* ShipInventoryComponent;

	/// -- Interact Mode
	// Bool to denote if in interact mode (true if in interact mode)
	bool bInInteractMode = false;

	// Bool to denote if Quick Interact is available
	bool bQuickInteract = false;

	// How long after pressing the player has to exit interact mode to quick interact
	float QuickInteractTime = 0.2f;

	/// Timer handle for handling the Quick Interact
	FTimerHandle QuickInteractHandle;

	// Pointer to object to lock too
	AActor* InteractableLockedTo;

	bool bIgnoreNextRelease;

	// Trace Data
	FVector	MouseWorldLocation;
	FVector MouseWorldDirection;
	FHitResult TraceHit = FHitResult(ForceInit);
	float PlacementDistance = 1000;

	// Pointer to last hit interactable
	TSoftObjectPtr<class ABaseInteractable> LastInteractedObject;

	// Maximum distance that the player can be before auto-deattaching from an attached interactable
	float DettachDistance = 250.0f;

	/// -- Camera
	// Bool to denote if in third person or first person (true if in third person)
	bool bInThirdPerson = false;

	// How much the value of PlayerCameraSpringArm changes per update
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float ZoomMultiplier = 10;

	// The minimum PlayerCameraSpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float MinZoomValue = 500;

	// The maximum PlayerCameraSpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float MaxZoomValue = 1000;

	/// -- Focusing
	// How much the camera fouses (changes Field of View) per update
	float FocusMultiplier = 0.08;

	// The percentage between the default and minimum FoV
	float FocusLerp = 1.0f;

	// The minimum FoV for focusing
	float MinFocus = 50.0f;

	// The interact modes FoV
	float InteractModeFocus = 85.0f;

	// The default FoV
	float DefaultFocus = 90.0f;
};
