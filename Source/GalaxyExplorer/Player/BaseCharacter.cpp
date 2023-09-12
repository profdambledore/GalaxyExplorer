// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BaseCharacter.h"
#include "BaseCharacter.h"
#include "Player/InteractWidget.h"
#include "Player/ShipInventoryComponent.h"
#include "Interactables/BaseInteractable.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(10.0f, 0.0f, 90.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	PlayerCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person Spring Arm"));
	PlayerCameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	PlayerCameraSpringArm->TargetArmLength = MinZoomValue + ((MaxZoomValue - MinZoomValue) / 2);
	PlayerCameraSpringArm->bUsePawnControlRotation = 1;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	ThirdPersonCamera->SetupAttachment(PlayerCameraSpringArm, USpringArmComponent::SocketName);

	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget Component"));

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Interaction Component"));
	WidgetInteractionComponent->SetRelativeLocation(FVector(10.0f, 0.0f, 90.0f));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;

	ShipInventoryComponent = CreateDefaultSubobject<UShipInventoryComponent>(TEXT("Ship Inventory Component"));

	// Set the active camera
	ThirdPersonCamera->SetActive(false, false);
	FirstPersonCamera->SetActive(true, true);

	// Get material object and store it
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT(""));
	if (CharacterMesh.Succeeded()) { GetMesh()->SetSkeletalMesh(CharacterMesh.Object); }

	// Find InteractWidget object and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Player/UI/WBP_InteractWidget"));
	if (UIClass.Succeeded()) {
		InteractWidgetComponent->SetWidgetClass(UIClass.Class);
	};

	// Set the InteractWidget to be hidden until needed
	InteractWidgetComponent->SetVisibility(false, false);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the players controller
	PC = Cast<APlayerController>(GetController());

	// Get reference to the interact widget class
	InteractWidget = Cast<UInteractWidget>(InteractWidgetComponent->GetWidget());	
	InteractWidget->OwningPlayer = this;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInInteractMode) {
		// Check if locked to an object
		if (InteractableLockedTo) {
			// If so, update the controllers rotation to look at said interactable
			PC->SetControlRotation((GetActorLocation() - InteractableLockedTo->GetActorLocation()).Rotation() + FRotator(0.0f, 180.0f, 0.0f));

			// Then check if the player has moved out of range.  If so, dettach.
			if (FVector::Dist(GetActorLocation(), InteractableLockedTo->GetActorLocation()) > DettachDistance) {
				InteractModeRelease();
			}
		}
		else {
			// Get cursor location in world space
			PC->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

			// Trace for interactables under the mouse
			GetWorld()->LineTraceSingleByChannel(TraceHit, MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * PlacementDistance), ECC_WorldStatic, FCollisionQueryParams(FName("DistTrace"), true));

			// First, check if the trace hit anything
			if (TraceHit.Actor != nullptr) {
				if (TraceHit.Actor->IsA(ABaseInteractable::StaticClass())) {
					if (LastInteractedObject == nullptr) {
						// Cast to the object
						LastInteractedObject = Cast<ABaseInteractable>(TraceHit.Actor);
						UpdateInteractWidget();
					}
					else {
						// Check if the LastInteractedObject and TraceHit.Actor are the same object
						if (LastInteractedObject->GetName() == TraceHit.Actor->GetName()) {
							// Don't cast again
						}
						else {
							// Replace the pointer in LastInteractedObject with the new TraceHit->Actor
							LastInteractedObject = Cast<ABaseInteractable>(TraceHit.Actor);
							UpdateInteractWidget();
						}
					}

					// Update the location of the interactable widget and make it visible
					InteractWidgetComponent->SetWorldLocation(LastInteractedObject->InteractionWidgetPos->GetComponentLocation());
					InteractWidgetComponent->SetWorldRotation(LastInteractedObject->InteractionWidgetPos->GetComponentRotation() + LastInteractedObject->WidgetRotation);
					InteractWidgetComponent->SetVisibility(true, true);

				}
				else {
					// Set last hit object to nullptr and hide the interactable widget
					LastInteractedObject = nullptr;
					InteractWidgetComponent->SetVisibility(false, false);
					InteractWidget->ClearInteractionList();
				}
			}
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &ABaseCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ABaseCharacter::MoveY);
	PlayerInputComponent->BindAxis("CameraX", this, &ABaseCharacter::CameraX);
	PlayerInputComponent->BindAxis("CameraY", this, &ABaseCharacter::CameraY);
	PlayerInputComponent->BindAxis("Zoom", this, &ABaseCharacter::ZoomThirdPersonCamera);
	PlayerInputComponent->BindAxis("Zoom", this, &ABaseCharacter::FocusCamera);
	PlayerInputComponent->BindAxis("InteractModeScroll", this, &ABaseCharacter::InteractModeScroll);

	// Add Action Binds
	PlayerInputComponent->BindAction("InteractMode", IE_Pressed, this, &ABaseCharacter::InteractModePress);
	PlayerInputComponent->BindAction("InteractMode", IE_Released, this, &ABaseCharacter::InteractModeRelease);
	PlayerInputComponent->BindAction("InteractMode_Primary", IE_Pressed, this, &ABaseCharacter::InteractModePrimaryPress);
	PlayerInputComponent->BindAction("InteractMode_Primary", IE_Released, this, &ABaseCharacter::InteractModePrimaryRelease);
	PlayerInputComponent->BindAction("SwapCamera", IE_Released, this, &ABaseCharacter::ToggleCameraMode);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::JumpPress);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::JumpRelease);
}

// --- Movement ---
void ABaseCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0) {
		// Move on the X axis based on the input's axis value
		AddMovementInput(GetActorForwardVector(), AxisValue, false);
	}
}

void ABaseCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0) {
		// Move on the Y axis based on the input's axis value
		AddMovementInput(GetActorRightVector(), AxisValue, false);
	}
}

void ABaseCharacter::CameraX(float AxisValue)
{
	if (AxisValue != 0) {
		// Check if we are in interact mode.  If so, 
		if (bInInteractMode) {

		}
		// Else, do normal camera movements
		else {
			// Rotate on the X axis based on the input's axis value
			AddControllerYawInput(AxisValue);
		}
	}
}

void ABaseCharacter::CameraY(float AxisValue)
{
	if (AxisValue != 0) {
		// Check if we are in interact mode.  If so, 
		if (bInInteractMode) {

		}
		// Else, do normal camera movements
		else {
			// Rotate on the Y axis based on the input's axis value
			AddControllerPitchInput(AxisValue);
		}
	}
}

void ABaseCharacter::JumpPress()
{
	ACharacter::Jump();
}

void ABaseCharacter::JumpRelease()
{
	ACharacter::StopJumping();
}

void ABaseCharacter::FocusCamera(float AxisValue)
{
	if (AxisValue != 0 && bInInteractMode)
	{
		if (AxisValue == 1)
		{
			FocusLerp -= FocusMultiplier;
			if (FocusLerp <= 0)
			{
				FocusLerp = 0.0f;
			}
			
		}
		else if (AxisValue == -1)
		{
			FocusLerp += FocusMultiplier;
			if (FocusLerp >= 1)
			{
				FocusLerp = 1.0f;
			}
		}
		FirstPersonCamera->SetFieldOfView(FMath::Lerp(MinFocus, InteractModeFocus, FocusLerp));
	}
}

void ABaseCharacter::ZoomThirdPersonCamera(float AxisValue)
{
	if (AxisValue != 0 && bInThirdPerson)
	{
		if (AxisValue == 1)
		{
			if (PlayerCameraSpringArm->TargetArmLength + ZoomMultiplier >= MaxZoomValue)
			{
				PlayerCameraSpringArm->TargetArmLength = MaxZoomValue;
			}
			else
			{
				PlayerCameraSpringArm->TargetArmLength = PlayerCameraSpringArm->TargetArmLength + ZoomMultiplier;
			}
		}
		else if (AxisValue == -1)
		{
			if (PlayerCameraSpringArm->TargetArmLength - ZoomMultiplier <= MinZoomValue)
			{
				PlayerCameraSpringArm->TargetArmLength = MinZoomValue;
			}
			else
			{
				PlayerCameraSpringArm->TargetArmLength = PlayerCameraSpringArm->TargetArmLength - ZoomMultiplier;
			}
		}
	}
}

// -- Interact Mode
void ABaseCharacter::InteractModePress()
{
	bInInteractMode = true;

	GetWorld()->GetTimerManager().ClearTimer(QuickInteractHandle);

	// Start Timer for Quick Interact
	bQuickInteract = true;
	GetWorld()->GetTimerManager().SetTimer(QuickInteractHandle, FTimerDelegate::CreateUObject(this, &ABaseCharacter::QuickInteract), QuickInteractTime, false, QuickInteractTime);

	// Modify first person camera's FoV to the interact mode value
	FirstPersonCamera->SetFieldOfView(InteractModeFocus);

	// Show mouse cursor on screen
	PC->bShowMouseCursor = true;
}

void ABaseCharacter::InteractModeRelease()
{
	if (!bIgnoreNextRelease) {
		bInInteractMode = false;

		// Reset bQuickInteract
		bQuickInteract = false;

		// Reset focusing (if required)
		FirstPersonCamera->SetFieldOfView(DefaultFocus);

		if (InteractableLockedTo) {
			Cast<ABaseInteractable>(InteractableLockedTo)->Interact_OnUnlock(this);
		}
		
		InteractableLockedTo = nullptr;

		// Hide mouse cursor 
		LastInteractedObject = nullptr;
		PC->bShowMouseCursor = false;
		InteractWidgetComponent->SetVisibility(false, false);
		InteractWidget->ClearInteractionList();
	}
	else {
		bIgnoreNextRelease = false;
	}
}

void ABaseCharacter::InteractModePrimaryPress()
{
	WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
}

void ABaseCharacter::InteractModePrimaryRelease()
{
	WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}


void ABaseCharacter::InteractModeScroll(float AxisValue)
{
	if (AxisValue != 0 && bInInteractMode)
	{
		if (AxisValue == 1)
		{
			WidgetInteractionComponent->PressPointerKey(EKeys::MouseScrollUp);
		}
		else if (AxisValue == -1)
		{
			WidgetInteractionComponent->PressPointerKey(EKeys::MouseScrollDown);

		}
	}
}

void ABaseCharacter::QuickInteract()
{
	// Fire a trace.  If hit an interactable, complete first event
	if (!bQuickInteract) {

	}

	// Reset bQuickInteract
	bQuickInteract = false;
}

void ABaseCharacter::AttachToInteractable(AActor* ActorToAttachTo)
{
	// Ignore the next interact mode release, if required
	// For example, when interacting with a panel
	bIgnoreNextRelease = true;
	InteractableLockedTo = ActorToAttachTo;

	// Set last hit object to nullptr and hide the interactable widget
	LastInteractedObject = nullptr;
	InteractWidgetComponent->SetVisibility(false, false);
}

void ABaseCharacter::UpdateInteractWidget()
{
	//InteractWidgetComponent->SetRelativeRotation(LastInteractedObject->WidgetRotation);
	InteractWidgetComponent->SetRelativeScale3D(LastInteractedObject->WidgetScale);

	if (LastInteractedObject.Get()->bEnabled == true) {
		InteractWidget->InterationMap = LastInteractedObject->InterationPoints;
	}
	else {
		InteractWidget->InterationMap = LastInteractedObject->InterationPointsPowerOff;
	}
	InteractWidget->UpdateInteractionList();
	InteractWidget->InteractionFocused = LastInteractedObject.Get();
	InteractWidgetComponent->SetVisibility(true, true);
}

void ABaseCharacter::ToggleCameraMode()
{
	if (bInThirdPerson == false)
	{
		FirstPersonCamera->SetActive(false, false);
		ThirdPersonCamera->SetActive(true, true);

		bInThirdPerson = true;
	}
	else if (bInThirdPerson == true) {
		FirstPersonCamera->SetActive(true, true);
		ThirdPersonCamera->SetActive(false, false);

		bInThirdPerson = false;
	}
}