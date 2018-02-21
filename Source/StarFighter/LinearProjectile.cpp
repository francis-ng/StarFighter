// Francis Ng 2017-2018

#include "LinearProjectile.h"

/// BeginPlay override
void ALinearProjectile::BeginPlay() {
	Super::BeginPlay();

	AcquireTarget();
	InitializeProjectile();
}

/// Initialization
void ALinearProjectile::InitializeProjectile() {
	initialDirection.Normalize();
	primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	UpdateLinearVelocity();
}

/// Sets the necessary target on fire
void ALinearProjectile::AcquireTarget() {
	if (targetsPlayer) {
		APawn* character = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (!character) {
			initialDirection = GetActorForwardVector();
		}
		else {
			initialDirection = character->GetActorLocation() - GetActorLocation();
		}
	}
	else {
		initialDirection = GetActorForwardVector();
	}
	initialDirection.Normalize();
}

/// Set whether the projectile is directed at the player
void ALinearProjectile::SetTargetsPlayer(bool isAimed) {
	Super::SetTargetsPlayer(isAimed);
	UpdateLinearVelocity();
}

/// Update the projectile's velocity
void ALinearProjectile::UpdateLinearVelocity() {
	primitive->SetPhysicsLinearVelocity(initialDirection * initialSpeed);
}