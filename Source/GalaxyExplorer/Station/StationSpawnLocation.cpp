// Fill out your copyright notice in the Description page of Project Settings.


#include "Station/StationSpawnLocation.h"

#include "Station/StationManager.h"

// Sets default values
AStationSpawnLocation::AStationSpawnLocation()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStationSpawnLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStationSpawnLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStationManager* AStationSpawnLocation::GetOwningStation()
{
	return nullptr;
}

