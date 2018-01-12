// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
	NormalizeMovementVectors();
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult *collisionResult = nullptr;
	if (currentMovement != FVector::ZeroVector) {
		FVector currentLocation = GetActorLocation();
		SetActorLocation(currentLocation + currentMovement * movementSpeed, true, OUT collisionResult);
	}
	DecayMultiplier(DeltaTime);
}

void AShip::Initialize() {
	currentMultiplier = maxMultiplier;
	decayPerSecond = (maxMultiplier - 1) / decayTime;
}

void AShip::NormalizeMovementVectors() {
	upDirection.Normalize();
	downDirection.Normalize();
	leftDirection.Normalize();
	rightDirection.Normalize();
}

void AShip::DecayMultiplier(float DeltaTime) {
	if (currentMultiplier > 1) {
		currentMultiplier -= decayPerSecond * DeltaTime;
		if (currentMultiplier < 1) {
			currentMultiplier = 1;
		}
	}
}

void AShip::MoveUp() {
	currentMovement += upDirection;
}

void AShip::MoveDown() {
	currentMovement += downDirection;
}

void AShip::MoveLeft() {
	currentMovement += leftDirection;
}

void AShip::MoveRight() {
	currentMovement += rightDirection;
}

void AShip::StopMoveUp() {
	currentMovement -= upDirection;
}

void AShip::StopMoveDown() {
	currentMovement -= downDirection;
}

void AShip::StopMoveLeft() {
	currentMovement -= leftDirection;
}

void AShip::StopMoveRight() {
	currentMovement -= rightDirection;
}

float AShip::GetScoreMultiplier() const {
	return currentMultiplier;
}

float AShip::GetBaseScore() const {
	return baseScore;
}