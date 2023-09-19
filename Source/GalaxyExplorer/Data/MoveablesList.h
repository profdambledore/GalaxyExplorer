// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MoveablesList.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct GALAXYEXPLORER_API FMoveablesList
{
public:
	GENERATED_BODY();

	// Array of UShipMoveables
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UShipMoveable*> Components;

	// Constructors / Destructors
	FMoveablesList();
	FMoveablesList(UShipMoveable* InitialMoveable);
	~FMoveablesList();
};
