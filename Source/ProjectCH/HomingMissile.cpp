// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingMissile.h"

void AHomingMissile::BeginPlay() {
	Super::BeginPlay();

	InitializeProjectile();
	AcquireTarget();
}

void AHomingMissile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	CalculateLifetime(DeltaTime);
	if (!IsTargetValid()) {
		AcquireTarget();
	}
	CalculateNextVector();
}

void AHomingMissile::InitializeProjectile() {
	initialDirection = GetActorForwardVector();
	initialDirection.Normalize();
	primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	if (!primitive) {
		UE_LOG(LogTemp, Error, TEXT("%s primitive cannot be set"), *GetName())
		return;
	}
	primitive->SetPhysicsLinearVelocity(initialDirection * initialSpeed);
	playerShip = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerShip) {
		UE_LOG(LogTemp, Error, TEXT("Player cannot be found"))
			return;
	}
}

void AHomingMissile::AcquireTarget() {
	if (targetsPlayer) {
		target = playerShip;
	}
	else {
		float minDistance = INT32_MAX;
		for (TActorIterator<AShip> EnemyItr(GetWorld()); EnemyItr; ++EnemyItr) {
			AShip* ship = *EnemyItr;
			if (ship == playerShip) continue;
			float distance = ship->GetDistanceTo(playerShip);
			if (distance < minDistance) {
				minDistance = distance;
				target = ship;
			}
		}
	}
}

void AHomingMissile::CalculateNextVector() {
	primitive->SetPhysicsLinearVelocity(primitive->GetPhysicsLinearVelocity().GetClampedToMaxSize(maxSpeed));
	if (IsTargetValid()) {
		FVector distance = target->GetActorLocation() - GetActorLocation();
		float tdelta = distance.Size() / Cast<AShip>(target)->GetSpeed() * predictionDeltaMod;
		FVector predictedTarget = target->GetActorLocation() + Cast<UPrimitiveComponent>(target->GetRootComponent())->GetPhysicsLinearVelocity() * tdelta;

		FVector currentVelocity = primitive->GetPhysicsLinearVelocity();
		FVector desiredVelocity = (predictedTarget - GetActorLocation()) * maxSpeed;
		FVector steering = desiredVelocity - currentVelocity;

		steering = steering.GetClampedToMaxSize(maxForce);

		primitive->AddForce(steering);
	}
}

bool AHomingMissile::IsTargetValid() const {
	if (!target) {
		return false;
	}
	if (target->IsPendingKill()) {
		return false;
	}
	return true;
}