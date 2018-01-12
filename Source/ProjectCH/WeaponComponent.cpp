// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeapon();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isFiring && !isBursting && timeleft <= 0) {
		isBursting = true;
	}
	if (isBursting) {
		BurstFire(DeltaTime);
	}
	else {
		CooldownWeapon(DeltaTime);
	}
}

void UWeaponComponent::CooldownWeapon(float DeltaTime)
{
	timeleft -= DeltaTime;
}

void UWeaponComponent::FireWeapon() {
	for (UActorComponent* Ahardpoint : projectileHardpoints) {
		USceneComponent* hardpoint = Cast<USceneComponent>(Ahardpoint);
		AMunition* ammo = Cast<AMunition>(theWorld->SpawnActor(projectile, &hardpoint->GetComponentTransform()));
		if (ammo) {
			ammo->SetTargetsPlayer(targetsPlayer);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Invalid ammo on %s"), *GetOwner()->GetName())
			return;
		}
	}
}

void UWeaponComponent::BurstFire(float DeltaTime)
{
	burstTimeLeft -= DeltaTime;
	if (burstTimeLeft <= 0) {
		FireWeapon();
		burstRemaining--;
		burstTimeLeft = burstCooldown;
	}
	if (burstRemaining <= 0) {
		isBursting = false;
		burstRemaining = burstCount;
		timeleft = cooldown;
		burstTimeLeft = 0.0f;
	}
}

void UWeaponComponent::InitializeWeapon() {
	projectileHardpoints = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), *hardpointTag);

	if (weaponName.IsEmpty()) {
		UE_LOG(LogTemp, Error, TEXT("No weapon name on %s"), *GetOwner()->GetName())
			return;
	}

	if (!projectile) {
		UE_LOG(LogTemp, Error, TEXT("No projectile for %s"), *GetOwner()->GetName())
			return;
	}
	if (projectileHardpoints.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("No weapon hardpoints %s"), *GetOwner()->GetName())
			return;
	}
	if (!weaponIcon) {
		UE_LOG(LogTemp, Error, TEXT("No icon for %s"), *GetOwner()->GetName())
			return;
	}

	theWorld = GetWorld();
	if (!theWorld) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get world"))
	}

	burstRemaining = burstCount;
}

bool UWeaponComponent::IsFiring() const {
	return isFiring;
}

bool UWeaponComponent::IsBursting() const {
	return isBursting;
}

void UWeaponComponent::SetFiring(bool firing) {
	isFiring = firing;
}

FString UWeaponComponent::GetName() const {
	return weaponName;
}

int32 UWeaponComponent::GetPriority() const {
	return weaponPriority;
}

UTexture2D* UWeaponComponent::GetIcon() const {
	return weaponIcon;
}