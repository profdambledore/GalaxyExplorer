// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Data/ShipData.h"

#include "ShipInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAXYEXPLORER_API UShipInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShipInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TArray<FShipData> GetPlayerShipList();

	UFUNCTION(BlueprintCallable)
		void AddShipToList(FShipData NewShip);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShipData> PlayerShipList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray < class ABaseShip* > ShipsPointers;
		
};
