// Francis Ng 2017-2018

#include "ShipPlayerController.h"

/// BeginPlay override
void AShipPlayerController::BeginPlay() {
	Super::BeginPlay();

}

/// SetPawn override to broadcast possessed event
void AShipPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	onPawnPossessed.Broadcast();
}

/// Get controlled ship
AShip* AShipPlayerController::GetControlledShip() const {
	return Cast<AShip>(GetPawn());
}
