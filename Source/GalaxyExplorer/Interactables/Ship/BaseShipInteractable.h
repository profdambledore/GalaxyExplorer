// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/BaseInteractable.h"


#include "BaseShipInteractable.generated.h"


UCLASS()
class GALAXYEXPLORER_API ABaseShipInteractable : public ABaseInteractable
{
	GENERATED_BODY()

public:
	void SetOwningShip(class ABaseShip* InShip);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
		 ABaseShip* OwningShip = nullptr;
};
