// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship/Gimbal/VTOLGimbal.h"

// Sets default values for this component's properties
UVTOLGimbal::UVTOLGimbal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT("/Game/Ship/Data/VTOLRotationCurve"));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; }
	
	// ...
}


// Called when the game starts
void UVTOLGimbal::BeginPlay()
{
	Super::BeginPlay();

	if (TimelineCurve) {
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("RotationTimelineProgress"));
		RotationTimeline.AddInterpFloat(TimelineCurve, TimelineProgress);
		RotationTimeline.SetLooping(false);
		//RotationTimeline.SetPlayRate(1 / VTOL_RotationSpeed);
	}
}


// Called every frame
void UVTOLGimbal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RotationTimeline.TickTimeline(DeltaTime);
	// ...
}

void UVTOLGimbal::ToggleVTOLMode(bool InVTOL)
{
	if (InVTOL) {
		RotationTimeline.Play();
		UE_LOG(LogTemp, Warning, TEXT("Tog"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tog"));
		RotationTimeline.Reverse();
	}
}

void UVTOLGimbal::RotationTimelineProgress(float Value)
{
	SetWorldRotation(FMath::Lerp(VTOL_Disabled, VTOL_Enabled, Value));
}

