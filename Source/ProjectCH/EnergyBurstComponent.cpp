// Fill out your copyright notice in the Description page of Project Settings.

#include "EnergyBurstComponent.h"


// Sets default values for this component's properties
UEnergyBurstComponent::UEnergyBurstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyBurstComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeapon();
}


// Called every frame
void UEnergyBurstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isFiring && !isBursting && CanFire()) {
		SetBurstStrength();
		healthComponent->EnergyRelease();
		isBursting = true;
	}
	if (isBursting) {
		BurstFire(DeltaTime);
	}
}

void UEnergyBurstComponent::InitializeWeapon() {
	projectileHardpoints = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), *hardpointTag);

	if (!projectile) {
		UE_LOG(LogTemp, Error, TEXT("No projectile for %s"), *GetOwner()->GetName())
			return;
	}
	if (projectileHardpoints.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("No weapon hardpoints %s"), *GetOwner()->GetName())
			return;
	}

	healthComponent = Cast<UHealthComponent>(GetOwner()->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!healthComponent) {
		UE_LOG(LogTemp, Error, TEXT("No health component for %s"), *GetOwner()->GetName())
			return;
	}

	theWorld = GetWorld();
	if (!theWorld) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get world"))
			return;
	}

	burstRemaining = burstCount;
}

void UEnergyBurstComponent::FireWeapon() {
	for (UActorComponent* Ahardpoint : projectileHardpoints) {
		USceneComponent* hardpoint = Cast<USceneComponent>(Ahardpoint);
		AMunition* ammo = Cast<AMunition>(theWorld->SpawnActor(projectile, &hardpoint->GetComponentTransform()));
		if (ammo) {
			ammo->SetTargetsPlayer(false);
			ammo->SetDamageMultiplier(damageMultiplier);
			ammo->SetInitialDirection(hardpoint->GetForwardVector());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Invalid ammo on %s"), *GetOwner()->GetName())
				return;
		}
	}
}

void UEnergyBurstComponent::BurstFire(float DeltaTime)
{
	burstTimeLeft -= DeltaTime;
	if (burstTimeLeft <= 0) {
		FireWeapon();
		burstRemaining--;
		burstTimeLeft = burstCooldown;
	}
	if (burstRemaining <= 0) {
		ResetBurstStrength();
		isBursting = false;
		burstRemaining = burstCount;
		burstTimeLeft = 0.0f;
	}
}

void UEnergyBurstComponent::SetBurstStrength() {
	float overchargeFraction = healthComponent->GetOvercharge() / healthComponent->GetMaxOvercharge();
	int32 calculatedBurst = floorf(maxBurstCount * overchargeFraction);
	float calculatedMultiplier = floorf(maxDamageMultiplier * overchargeFraction);

	burstCount = calculatedBurst < 1 ? 1 : calculatedBurst;
	burstRemaining = burstCount;
	damageMultiplier = calculatedMultiplier < 1 ? 1 : calculatedMultiplier;
}

void UEnergyBurstComponent::ResetBurstStrength() {
	burstCount = 1;
	burstRemaining = 1;
	damageMultiplier = 1;
}

bool UEnergyBurstComponent::CanFire() const {
	return healthComponent->GetCurrentShield() == healthComponent->GetMaxShield();
}

bool UEnergyBurstComponent::IsFiring() const {
	return isFiring;
}

bool UEnergyBurstComponent::IsBursting() const {
	return isBursting;
}

void UEnergyBurstComponent::SetFiring(bool firing) {
	isFiring = firing;
}