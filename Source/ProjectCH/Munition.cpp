// Francis Ng 2017-2018

#include "Munition.h"


/// Contructor
AMunition::AMunition()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/// BeginPlay override or when spawned
void AMunition::BeginPlay()
{
	Super::BeginPlay();
}

/// Tick override
void AMunition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateLifetime(DeltaTime);
	//TurnToDirectionOfMovement();
}

/// Initialization
void AMunition::InitializeProjectile() {
	initialDirection.Normalize();
	primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	primitive->SetPhysicsLinearVelocity(initialDirection * initialSpeed);
}

/// Set whether ammunition is targeted at player
void AMunition::SetTargetsPlayer(bool isAimed) {
	targetsPlayer = isAimed;
	AcquireTarget();
}

/// Set the initial direction of the projectile
void AMunition::SetInitialDirection(FVector direction) {
	initialDirection = direction;
}

/// Sets the actor rotation to direction of movement
void AMunition::TurnToDirectionOfMovement() {
	FVector velocity = primitive->GetComponentVelocity();
	SetActorRotation(velocity.ForwardVector.Rotation());
}

/// Calculate the amount of time left before despawn
void AMunition::CalculateLifetime(float DeltaTime) {
	timeToLive -= DeltaTime;
	if (timeToLive <= 0) {
		if (!Destroy()) {
			UE_LOG(LogTemp, Warning, TEXT("%s cannot be destroyed"), *GetName())
		}
	}
}

/// Default target acquisition
void AMunition::AcquireTarget() {
	initialDirection = GetActorForwardVector();
}

#pragma region Getters
float AMunition::GetDamage() const {
	return damage * damageMultiplier;
}

float AMunition::GetDamageMultiplier() const {
	return damageMultiplier;
}
#pragma endregion

/// Set damage multiplier
void AMunition::SetDamageMultiplier(float multiplier) {
	damageMultiplier = multiplier;
}