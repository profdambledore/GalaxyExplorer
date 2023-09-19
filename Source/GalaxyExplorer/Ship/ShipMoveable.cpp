// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/ShipMoveable.h"

// Sets default values for this component's properties
UShipMoveable::UShipMoveable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Find and store the timelines curve
	ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT("/Game/Ship/Data/VTOLRotationCurve"));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; }
	// ...
}


// Called when the game starts
void UShipMoveable::BeginPlay()
{
	Super::BeginPlay();

	// Setup the timeline
	if (TimelineCurve) {
		FOnTimelineFloat MoveableTimelineProgress;
		MoveableTimelineProgress.BindUFunction(this, FName("MoveableTimelineProgress"));
		MoveableTimeline.AddInterpFloat(TimelineCurve, MoveableTimelineProgress);
		MoveableTimeline.SetLooping(false);

		// Set the timeline speed to play in the inputted speed
		MoveableTimeline.SetPlayRate(1 / Movable_TransitionSpeed);
	}
	
}


// Called every frame
void UShipMoveable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tick the timeline
	MoveableTimeline.TickTimeline(DeltaTime);
	
}

int UShipMoveable::ToggleMoveable(int State)
{
	// If State = 1, then toggle the timeline
	if (State == 1) {
		bMoveableActive = !bMoveableActive;
		if (bMoveableActive) {
			MoveableTimeline.Play();
			return 1;
		}
		else {
			MoveableTimeline.Reverse();
			return -1;
		}
	}
	// If State = 2, then reverse the timeline, even if it has already reached the start
	else if (State == 2) {
		bMoveableActive = false;
		MoveableTimeline.Reverse();
		return -1;

	}
	// If State = 3, then play the timeline, even if it has already reached the end
	else if (State == 3) {
		bMoveableActive = true;
		MoveableTimeline.Play();
		return 1;
	}
	return 0;
}

void UShipMoveable::MoveableTimelineProgress(float Value)
{
	// Lerp between the two location and rotation values set on the movable object
	SetRelativeLocation(FMath::Lerp(Movable_Disabled.GetLocation(), Movable_Enabled.GetLocation(), Value));
	SetRelativeRotation(FMath::Lerp(Movable_Disabled.GetRotation(), Movable_Enabled.GetRotation(), Value));
}

void UShipMoveable::OnMoveableTimelineStart(bool bForward)
{
}

void UShipMoveable::OnMoveableTimelineEnd(bool bForward)
{
}

