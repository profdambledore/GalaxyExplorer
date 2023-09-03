// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Data/ShipManufacturer.h"
#include "Data/ShipClassification.h"

#include "ShipData.generated.h"

USTRUCT(BlueprintType)
struct GALAXYEXPLORER_API FShipData : public FTableRowBase
{
public:
	GENERATED_BODY();

	// Change back to edit defaults only

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EShipManufacturer> Manufacturer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class ABaseShip> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EShipClassification> Classification;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Status; // Replace with ENUM

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Cargo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int CargoMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Crew;

	FShipData();
	FShipData(FString InName, TEnumAsByte<EShipManufacturer> InManufacturer, TSubclassOf<class ABaseShip> InClass, TEnumAsByte<EShipClassification> InClassification, FString InStatus, FString InLocation, int InCargo, int InCargoMax, int InCrew);
	~FShipData();
};

