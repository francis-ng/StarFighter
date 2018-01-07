// Fill out your copyright notice in the Description page of Project Settings.

#include "Munition.h"


// Sets default values
AMunition::AMunition()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMunition::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMunition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateLifetime(DeltaTime);
	//TurnToDirectionOfMovement();
}

void AMunition::InitializeProjectile() {
	initialDirection.Normalize();
	primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	primitive->SetPhysicsLinearVelocity(initialDirection * initialSpeed);
}

void AMunition::SetTargetsPlayer(bool isAimed) {
	targetsPlayer = isAimed;
	AcquireTarget();
}

void AMunition::SetInitialDirection(FVector direction) {
	initialDirection = direction;
}

void AMunition::TurnToDirectionOfMovement() {
	FVector velocity = primitive->GetComponentVelocity();
	SetActorRotation(velocity.ForwardVector.Rotation());
}

void AMunition::CalculateLifetime(float DeltaTime) {
	timeToLive -= DeltaTime;
	if (timeToLive <= 0) {
		if (!Destroy()) {
			UE_LOG(LogTemp, Warning, TEXT("%s cannot be destroyed"), *GetName())
		}
	}
}

void AMunition::AcquireTarget() {
	initialDirection = GetActorForwardVector();
}

float AMunition::GetDamage() const {
	return damage;
}