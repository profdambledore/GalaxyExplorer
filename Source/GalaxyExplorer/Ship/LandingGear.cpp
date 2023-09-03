// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/LandingGear.h"

// Sets default values for this component's properties
ULandingGear::ULandingGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULandingGear::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULandingGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULandingGear::ToggleLandingGear(bool bInEnabled)
{
	if (bInEnabled) {
		SetRelativeTransform(GearEnabled);
	}
	else {
		SetRelativeTransform(GearDisabled);
	}
}

