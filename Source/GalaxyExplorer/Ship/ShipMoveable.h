// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Components/TimelineComponent.h"

#include "ShipMoveable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAXYEXPLORER_API UShipMoveable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShipMoveable();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Play or reverse the MoveableTimeline to the inputted state
	UFUNCTION(BlueprintCallable)
		int ToggleMoveable(int State); // 1 = toggle, 2 = close, 3 = open

	// Tick event for the timeline
	UFUNCTION()
		void MoveableTimelineProgress(float Value);

	UFUNCTION()
		void OnMoveableTimelineStart(bool bForward);

	UFUNCTION()
		void OnMoveableTimelineEnd(bool bForward);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	// -- Gimbal Details
	// Transform for how the landing gear should be orientated when disabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FTransform Movable_Disabled;

	// Transform for how the landing gear should be orientated when enabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FTransform Movable_Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gimbal Details")
		float Movable_TransitionSpeed;

	// -- Timeline
	// The timeline object itself
	FTimeline MoveableTimeline;

	bool bMoveableActive = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline Details")
		UCurveFloat* TimelineCurve = nullptr;
		
};
