// Francis Ng 2017-2018

#include "ShipAIController.h"

/// BeginPlay override
void AShipAIController::BeginPlay() {
	Super::BeginPlay();

}

/// TickComponent override
void AShipAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

/// Possess override to store ship reference and weapons
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

/// Get the controlled ship
AShip* AShipAIController::GetControlledShip() const {
	return Cast<AShip>(GetPawn());
}