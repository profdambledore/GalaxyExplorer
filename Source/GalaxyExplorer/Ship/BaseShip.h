// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Data/ShipData.h"

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
		void TurnShipOn();

	UFUNCTION(BlueprintCallable)
		void FlightReady();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* ShipMesh;

	// -- Ship Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Data")
		FShipData ShipData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ABaseShipInteractable*> Interactables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class UVTOLGimbal*> VTOLGimbals;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Data")
		TArray<class ULandingGear*> LandingGears;

};
