// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BaseCharacter.h"
#include "BaseCharacter.h"

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

	// Set the active camera
	ThirdPersonCamera->SetActive(false, false);
	FirstPersonCamera->SetActive(true, true);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the players controller
	PC = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ABaseCharacter::ZoomThirdPersonCamera);

	// Add Action Binds
	PlayerInputComponent->BindAction("InteractMode", IE_Pressed, this, &ABaseCharacter::InteractModePress);
	PlayerInputComponent->BindAction("InteractMode", IE_Released, this, &ABaseCharacter::InteractModeRelease);
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
	bInInteractMode = false;

	// Reset bQuickInteract
	bQuickInteract = false;

	// Reset focusing (if required)
	FirstPersonCamera->SetFieldOfView(DefaultFocus);

	// Hide mouse cursor 
	PC->bShowMouseCursor = false;
}

void ABaseCharacter::QuickInteract()
{
	// Fire a trace.  If hit an interactable, complete first event
	if (bQuickInteract) {

	}

	// Reset bQuickInteract
	bQuickInteract = false;
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