// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Data/ShipData.h"

#include "StationManager.generated.h"

class AShipManagerPanel;
class UShipManagerUI;

UCLASS()
class GALAXYEXPLORER_API AStationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStationManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AStationSpawnLocation* GetSuitableSpawnLocation(TEnumAsByte<EShipClassification> InClass);

	UFUNCTION(BlueprintCallable)
		FString SpawnShip(FShipData InShipData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root = nullptr;

	// -- Station Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Objects")
		TArray<class AStationSpawnLocation*> SpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Objects")
		TArray<class AFleetManagerPanel*> FleetManagers;

	// -- Station Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Properties")
		FString StationName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Properties")
		FString StationCode = "";
};
