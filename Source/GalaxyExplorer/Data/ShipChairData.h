// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShipChairData.generated.h"

USTRUCT(BlueprintType)
struct GALAXYEXPLORER_API FShipChairData
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class AShipChair* Chair = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class ABaseCharacter* Player = nullptr;

	// Constructors / Destructors
	FShipChairData();
	FShipChairData(FName NewName, AShipChair* NewChair);
	~FShipChairData();
};

