// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/LandingGear.h"

// Sets default values for this component's properties
ULandingGear::ULandingGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT("/Game/Ship/Data/VTOLRotationCurve"));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; }
	// ...
}


// Called when the game starts
void ULandingGear::BeginPlay()
{
	Super::BeginPlay();

	if (TimelineCurve) {
		FOnTimelineFloat LandingGearTimelineProgress;
		LandingGearTimelineProgress.BindUFunction(this, FName("LandingGearTimelineProgress"));
		LandingGearTimeline.AddInterpFloat(TimelineCurve, LandingGearTimelineProgress);
		LandingGearTimeline.SetLooping(false);
		//RotationTimeline.SetPlayRate(1 / VTOL_RotationSpeed);
	}
	
}


// Called every frame
void ULandingGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LandingGearTimeline.TickTimeline(DeltaTime);
}

void ULandingGear::ToggleLandingGear(bool bInEnabled)
{
	if (bInEnabled) {
		UE_LOG(LogTemp, Warning, TEXT("Call"));
		LandingGearTimeline.Play();
	}
	else {
		LandingGearTimeline.Reverse();
	}
}

void ULandingGear::LandingGearTimelineProgress(float Value)
{
	SetRelativeLocation(FMath::Lerp(Gear_Disabled.GetLocation(), Gear_Enabled.GetLocation(), Value));
	SetWorldRotation(FMath::Lerp(Gear_Disabled.GetRotation(), Gear_Enabled.GetRotation(), Value));
}

