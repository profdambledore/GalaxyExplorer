// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StationSpawnLocation.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root = nullptr;

	// -- Station 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
		class AStationManager* Station = nullptr;

	// -- Spawn Location Details
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Location Details")
		FString SpawnLocationName = "";
};
