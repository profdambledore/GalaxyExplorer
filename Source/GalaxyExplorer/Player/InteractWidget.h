// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ListView.h"

#include "InteractWidget.generated.h"

UCLASS()
class GALAXYEXPLORER_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;

	void UpdateInteractionList(TMap<int, FString>);

public:
	// References
	UPROPERTY(BlueprintReadOnly, Category = "References")
		class ABaseCharacter* OwningPlayer = nullptr;

	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UListView* InteractList = nullptr;
};
