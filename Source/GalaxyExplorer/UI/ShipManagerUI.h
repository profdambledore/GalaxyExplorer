// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"

#include "ShipManagerUI.generated.h"

UCLASS()
class GALAXYEXPLORER_API UShipManagerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateFleetList();

	UFUNCTION()
		void ClearFleetList();

	UFUNCTION()
		void UpdateManagerSwitcher(int Index);

public:
	// References
	UPROPERTY(BlueprintReadOnly, Category = "References")
		class ABaseCharacter* OwningPlayer = nullptr;

	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UListView* FleetList = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWidgetSwitcher* ManagerSwitcher = nullptr;
	
};
