// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAIController.h"

void AShipAIController::BeginPlay() {
	Super::BeginPlay();

}

void AShipAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AShipAIController::Possess(APawn* InPawn) {
	controlledShip = Cast<AShip>(InPawn);
	if (!controlledShip) {
		UE_LOG(LogTemp, Error, TEXT("%s cannot find controlled ship"), *GetOwner()->GetName())
	}
	controlledShipWeapon = Cast<UWeaponComponent>(controlledShip->GetComponentByClass(UWeaponComponent::StaticClass()));
	if (!controlledShipWeapon) {
		UE_LOG(LogTemp, Error, TEXT("%s cannot find controlled ship's weapon"), *GetOwner()->GetName())
	}
	controlledShipWeapon->SetFiring(true);

	controlledShip->MoveForward();
}

AShip* AShipAIController::GetControlledShip() const {
	return Cast<AShip>(GetPawn());
}