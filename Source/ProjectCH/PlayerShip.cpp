// Francis Ng 2017-2018

#include "PlayerShip.h"

/// Constructor
APlayerShip::APlayerShip() {
	PrimaryActorTick.bCanEverTick = true;
}

/// Bind input events to keys
void APlayerShip::SetupPlayerInputComponent(UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	if (InputComponent) {
		InputComponent->BindAction("Move Up", IE_Pressed, this, &Super::MoveUp);
		InputComponent->BindAction("Move Up", IE_Released, this, &Super::StopMoveUp);
		InputComponent->BindAction("Move Down", IE_Pressed, this, &Super::MoveDown);
		InputComponent->BindAction("Move Down", IE_Released, this, &Super::StopMoveDown);
		InputComponent->BindAction("Move Left", IE_Pressed, this, &Super::MoveLeft);
		InputComponent->BindAction("Move Left", IE_Released, this, &Super::StopMoveLeft);
		InputComponent->BindAction("Move Right", IE_Pressed, this, &Super::MoveRight);
		InputComponent->BindAction("Move Right", IE_Released, this, &Super::StopMoveRight);
	}
}

/// Tick override
void APlayerShip::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	IncrementNoDamageMultiplier(DeltaTime);
}

/// Increment no damage multiplier by time passed
void APlayerShip::IncrementNoDamageMultiplier(float DeltaTime) {
	timePassed += DeltaTime;
	if (timePassed >= noDamageMultiplierTimestep) {
		currentNoDamageMultiplier += noDamageMultiplierIncrement;
		timePassed = 0;
		onNoDamageMultiplierUpdate.Broadcast(currentNoDamageMultiplier);
	}
}

/// Reset the no damage multiplier
void APlayerShip::ResetNoDamageMultiplier() {
	timePassed = 0;
	currentNoDamageMultiplier = 1;
	onNoDamageMultiplierUpdate.Broadcast(currentNoDamageMultiplier);
}

/// Get the no damage multiplier
float APlayerShip::GetNoDamageMultiplier() const {
	return currentNoDamageMultiplier;
}