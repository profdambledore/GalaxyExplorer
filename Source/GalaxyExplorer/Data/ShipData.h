// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Data/ShipManufacturer.h"

#include "ShipData.generated.h"

USTRUCT(BlueprintType)
struct GALAXYEXPLORER_API FShipData : public FTableRowBase
{
public:
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TEnumAsByte<EShipManufacturer> Manufacturer;;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class ABaseShip> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Status; // Replace with ENUM

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Cargo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int CargoMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int Crew;

	FShipData();
	FShipData(FString InName, TEnumAsByte<EShipManufacturer> InManufacturer, TSubclassOf<class ABaseShip> InClass, FString InStatus, FString InLocation, int InCargo, int InCargoMax, int InCrew);
	~FShipData();
};

