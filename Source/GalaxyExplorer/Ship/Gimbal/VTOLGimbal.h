// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "VTOLGimbal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAXYEXPLORER_API UVTOLGimbal : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVTOLGimbal();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void ToggleVTOLMode(bool InVTOL);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// -- Gimbal Details
	// Rotator for how the gimbal should be orientated when VTOL mode is disabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FRotator VTOL_Disabled;

	// Rotator for how the gimbal should be orientated when VTOL mode is enabled
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gimbal Details")
		FRotator VTOL_Enabled;

		
};
