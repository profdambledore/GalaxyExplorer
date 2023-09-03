// Fill out your copyright notice in the Description page of Project Settings.

#include "Station/StationSpawnLocation.h"

#include "Station/StationManager.h"
#include "Ship/BaseShip.h"

// Sets default values
AStationSpawnLocation::AStationSpawnLocation()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Spawn Collision"));
	SpawnCollision->SetupAttachment(Root, "");

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStationSpawnLocation::BeginPlay()
{
	Super::BeginPlay();

	// Add Overlap Events
	SpawnCollision->OnComponentBeginOverlap.AddDynamic(this, &AStationSpawnLocation::OnSCBeginOverlap);
	SpawnCollision->OnComponentEndOverlap.AddDynamic(this, &AStationSpawnLocation::OnSCEndOverlap);
	
}

// Called every frame
void AStationSpawnLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStationManager* AStationSpawnLocation::GetOwningStation()
{
	return Station;
}

void AStationSpawnLocation::OnSCBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Overlaps++;
}

void AStationSpawnLocation::OnSCEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Overlaps--;
}

bool AStationSpawnLocation::SpawnShipAtLocation(FShipData InShipData)
{
	// Spawn ship
	FVector wL = SpawnCollision->GetComponentLocation();
	ABaseShip* NewShip = GetWorld()->SpawnActor<ABaseShip>(InShipData.Class, FVector(wL.X, wL.Y, wL.Z - (SpawnCollision->GetScaledBoxExtent().Z)), FRotator());
	bInUse = true;
	return true;
}

TEnumAsByte<EShipClassification> AStationSpawnLocation::ReturnPadData()
{
	return PadMax;
}

bool AStationSpawnLocation::PadNotInUse()
{
	if (Overlaps == 0 && !bInUse) {
		return true;
	}
	return false;
}

