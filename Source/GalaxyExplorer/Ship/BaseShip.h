// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/LightComponent.h"

#include "Data/ShipData.h"
#include "Data/MoveablesList.h"
#include "Data/ThrusterData.h"
#include "Data/ShipChairData.h"

#include "BaseShip.generated.h"

UCLASS()
class GALAXYEXPLORER_API ABaseShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ToggleShipOn();

	UFUNCTION(BlueprintCallable)
		void FlightReady();

	/// -- Toggles
	// Toggles the state of all landing gears
	UFUNCTION()
		void ToggleLandingGear();

	// Toggles the state of all exterior lights
	UFUNCTION()
		void ToggleExteriorLights();

	// Toggles the state of all interior lights
	UFUNCTION()
		void ToggleInteriorLights();

	// Toggles the state of all VTOL gimbals
	UFUNCTION()
		void ToggleVTOLMode();

	// Toggles the state of all Movables of the inputted category
	UFUNCTION()
		void ToggleMoveables(FName TagName, bool bIsDoor);

	// Toggles the state of all doors to be closed if one is open, or open if all are closed
	UFUNCTION(BlueprintCallable)
		void CloseAllDoors();

	void RemoveCharacterFromSeat(class ABaseCharacter* CharacterToRemove);

	int FindSeat(FName SeatName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* ShipMesh;

	/// -- Ship Data
	// The data struct of the ship
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Data")
		FShipData ShipData;

	// Array of all interactables located in the ship
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ABaseShipInteractable*> Interactables;

	// Array of all VTOL Gimbals objects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class UVTOLGimbal*> VTOLGimbals;

	// Array of all Landing Gear objects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ULandingGear*> LandingGears;

	// Array of all exterior light objects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ULightComponent*> ExteriorLights;

	// Array of all interior light objects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ULightComponent*> InteriorLights;

	// Array of all moveables, sorted based on their gameplay tags
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TMap < FName, FMoveablesList> Moveables;

	// Array of all chairs in the ship, sorted based on their names (pilot, co-pilot)
	UPROPERTY(EditAnywhere, Category = "Ship Data")
		TArray<FShipChairData> Chairs;

	/// -- Ship Actives
	// True if the landing gear is down
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Actives")
		bool bLandingGearDown = false;

	// True if the exterior lights are on
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Actives")
		bool bExLightsOn = true;

	// True if the interior lights are on
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Actives")
		bool bInLightsOn = true;

	// True if the ship is in VTOL mode
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Actives")
		bool bInVTOLMode = false;

	// int to count how many doors are open
	int doorsOpen = 0;

	/// -- Ship Power
	bool bPoweredOn = false;
	bool bEnginesOn = false;

	/// -- Players in Ship
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Players in Ship")
		//TMap < FName, class ABaseCharacter*> PlayersInSeats;
};
