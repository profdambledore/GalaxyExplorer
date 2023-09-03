// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/ShipData.h"
#include "Ship/BaseShip.h"

FShipData::FShipData()
{

}
FShipData::FShipData(FString InName, TEnumAsByte<EShipManufacturer> InManufacturer, TSubclassOf<class ABaseShip> InClass, TEnumAsByte<EShipClassification> InClassification, FString InStatus, FString InLocation, int InCargo, int InCargoMax, int InCrew)
{
	Name = InName;
	Manufacturer = InManufacturer;
	Class = InClass;
	Classification = InClassification;
	Status = InStatus;
	Location = InLocation;
	Cargo = InCargo;
	CargoMax = InCargoMax;
	Crew = InCrew;
};


FShipData::~FShipData()
{

};
