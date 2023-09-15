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

	UFUNCTION(BlueprintCallable)
		int ToggleMoveable(int State); // 1 = toggle, 2 = close, 3 = open

	UFUNCTION()
		void MoveableTimelineProgress(float Value);


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
	FTimeline MoveableTimeline;

	bool bMoveableActive = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline Details")
		UCurveFloat* TimelineCurve = nullptr;
		
};
