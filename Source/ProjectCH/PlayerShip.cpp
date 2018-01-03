// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShip.h"

APlayerShip::APlayerShip() {
	PrimaryActorTick.bCanEverTick = true;
}

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

void APlayerShip::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}