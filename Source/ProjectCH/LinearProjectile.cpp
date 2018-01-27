// Fill out your copyright notice in the Description page of Project Settings.

#include "LinearProjectile.h"

void ALinearProjectile::BeginPlay() {
	Super::BeginPlay();

	AcquireTarget();
	InitializeProjectile();
}

void ALinearProjectile::InitializeProjectile() {
	initialDirection.Normalize();
	primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	UpdateLinearVelocity();
}

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

void ALinearProjectile::SetTargetsPlayer(bool isAimed) {
	Super::SetTargetsPlayer(isAimed);
	UpdateLinearVelocity();
}

void ALinearProjectile::UpdateLinearVelocity() {
	primitive->SetPhysicsLinearVelocity(initialDirection * initialSpeed);
}