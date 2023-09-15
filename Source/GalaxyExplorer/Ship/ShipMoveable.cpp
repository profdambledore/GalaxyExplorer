// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/ShipMoveable.h"

// Sets default values for this component's properties
UShipMoveable::UShipMoveable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT("/Game/Ship/Data/VTOLRotationCurve"));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; }
	// ...
}


// Called when the game starts
void UShipMoveable::BeginPlay()
{
	Super::BeginPlay();

	if (TimelineCurve) {
		FOnTimelineFloat MoveableTimelineProgress;
		MoveableTimelineProgress.BindUFunction(this, FName("MoveableTimelineProgress"));
		MoveableTimeline.AddInterpFloat(TimelineCurve, MoveableTimelineProgress);
		MoveableTimeline.SetLooping(false);
		//RotationTimeline.SetPlayRate(1 / VTOL_RotationSpeed);
	}
	
}


// Called every frame
void UShipMoveable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveableTimeline.TickTimeline(DeltaTime);
	
}

int UShipMoveable::ToggleMoveable(int State)
{
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
	else if (State == 2) {
		bMoveableActive = false;
		MoveableTimeline.Reverse();
		return -1;

	}
	else if (State == 3) {
		bMoveableActive = true;
		MoveableTimeline.Play();
		return 1;
	}
	return 0;
}

void UShipMoveable::MoveableTimelineProgress(float Value)
{
	SetRelativeLocation(FMath::Lerp(Movable_Disabled.GetLocation(), Movable_Enabled.GetLocation(), Value));
	SetWorldRotation(FMath::Lerp(Movable_Disabled.GetRotation(), Movable_Enabled.GetRotation(), Value));
}

