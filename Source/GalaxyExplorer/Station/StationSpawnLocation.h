// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "Data/ShipData.h"
#include "Data/ShipClassification.h"

#include "StationSpawnLocation.generated.h"

class ABaseShip;
class UShipInventoryComponent;

UCLASS()
class GALAXYEXPLORER_API AStationSpawnLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStationSpawnLocation();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AStationManager* GetOwningStation();

	// Overlap Functions
	UFUNCTION()
		void OnSCBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnSCEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		bool SpawnShipAtLocation(FShipData InShipData, int Index, UShipInventoryComponent* OwningInvent);

	TEnumAsByte<EShipClassification> ReturnPadData();
	bool PadNotInUse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* SpawnCollision = nullptr;

	// -- References 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
		class AStationManager* Station = nullptr;

	// -- Spawn Location Details
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Location Details")
		FString SpawnLocationName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn Location Details")
		TEnumAsByte<EShipClassification> PadMax;

	// --  Queries
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Queries")
		int Overlaps = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Queries")
		bool bInUse = false;
};
