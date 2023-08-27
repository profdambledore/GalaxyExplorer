// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/ChildActorComponent.h"
#include "Components/WidgetComponent.h"

#include "FleetManagerPanel.generated.h"

UCLASS()
class GALAXYEXPLORER_API AFleetManagerPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFleetManagerPanel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AStationManager* GetOwningStation();

	void UpdateStationName(FString InName, class AStationManager* InStation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// -- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* PanelComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* ButtonComponent = nullptr;


	// -- Refs
	class APanelButton* Button = nullptr;

	class AShipManagerPanel* Panel = nullptr;

	// -- Station 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
		class AStationManager* Station = nullptr;
};
