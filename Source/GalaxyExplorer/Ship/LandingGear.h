// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Components/TimelineComponent.h"

#include "LandingGear.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAXYEXPLORER_API ULandingGear : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULandingGear();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void ToggleLandingGear(bool bInEnabled);

	UFUNCTION()
		void LandingGearTimelineProgress(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// -- Gimbal Details
	// Transform for how the landing gear should be orientated when disabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FTransform Gear_Disabled;

	// Transform for how the landing gear should be orientated when enabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FTransform Gear_Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gimbal Details")
		float Gear_TransitionSpeed;

	// -- Timeline
	FTimeline LandingGearTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline Details")
		UCurveFloat* TimelineCurve = nullptr;
};
