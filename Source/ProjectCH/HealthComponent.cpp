// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = maxHealth;
	currentShield = maxShield;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	RecoverShield(shieldRechargeRate * DeltaTime);
}

void UHealthComponent::DealDamage(float damage) {
	shieldOvercharge -= damage;
	if (shieldOvercharge < 0) {
		currentShield += shieldOvercharge;
		shieldOvercharge = 0;
	}
	if (currentShield < 0) {
		currentHealth += currentShield;
		currentShield = 0;
		onHealthUpdate.Broadcast();
	}
	if (!IsAlive()) {
		onDeath.Broadcast();
	}
	onShieldUpdate.Broadcast();
}

void UHealthComponent::RecoverHealth(float amount) {
	currentHealth += amount;
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
	onHealthUpdate.Broadcast();
}

void UHealthComponent::RecoverShield(float amount) {
	if (currentShield < maxShield) {
		currentShield += amount;
		if (currentShield > maxShield) {
			currentShield = maxShield;
		}
		onShieldUpdate.Broadcast();
	}
}

void UHealthComponent::Overcharge(float amount) {
	if (currentShield < maxShield) {
		currentShield += amount;
		if (currentShield > maxShield) {
			shieldOvercharge = currentShield - maxShield;
			currentShield = maxShield;
		}
	}
	shieldOvercharge += amount;
	if (shieldOvercharge > maxShield*maxOverchargeMultiplier) {
		shieldOvercharge = maxShield*maxOverchargeMultiplier;
	}
	onShieldUpdate.Broadcast();
}

float UHealthComponent::EnergyRelease() {
	float energyReleased = GetTotalEnergy();
	currentShield = 0;
	shieldOvercharge = 0;
	onShieldUpdate.Broadcast();
	return energyReleased;
}

float UHealthComponent::GetMaxHealth() const {
	return maxHealth;
}

float UHealthComponent::GetMaxShield() const {
	return maxShield;
}

float UHealthComponent::GetMaxOvercharge() const {
	return maxShield*maxOverchargeMultiplier;
}

float UHealthComponent::GetCurrentHealth() const {
	return currentHealth;
}

float UHealthComponent::GetCurrentShield() const {
	return currentShield;
}

float UHealthComponent::GetOvercharge() const {
	return shieldOvercharge;
}

float UHealthComponent::GetTotalEnergy() const {
	return currentShield + shieldOvercharge;
}

bool UHealthComponent::IsAlive() const {
	return currentHealth > 0;
}

EDamageLevelEnum UHealthComponent::GetDamageLevel() const {
	float damagePercentage = currentHealth / maxHealth;
	if (damagePercentage <= damagedHealthPercentage) {
		return EDamageLevelEnum::DL_Damaged;
	}
	if (damagePercentage <= criticalHealthPercentage) {
		return EDamageLevelEnum::DL_Critical;
	}
	return EDamageLevelEnum::DL_Healthy;
}