// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipPlayerController.h"

void AShipPlayerController::BeginPlay() {
	Super::BeginPlay();

}

void AShipPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	onPawnPossessed.Broadcast();
}

AShip* AShipPlayerController::GetControlledShip() const {
	return Cast<AShip>(GetPawn());
}
