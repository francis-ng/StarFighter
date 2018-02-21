// Francis Ng 2017-2018

#include "WeaponManagerComponent.h"

/// Contructor for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/// BeginPlay override
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeaponManager();
}

/// Initialization of data for player weapons
void UWeaponManagerComponent::InitializeWeaponManager()
{	
	auto weapons = GetOwner()->GetComponentsByClass(UWeaponComponent::StaticClass());
	numberOfWeapons = weapons.Num();
	currentWeaponIndex = 0;
	if (numberOfWeapons == 0) {
		UE_LOG(LogTemp, Error, TEXT("No weapons on %s"), *GetOwner()->GetName())
		return;
	}
	for (int32 i = 0; i < numberOfWeapons; i++) {
		UWeaponComponent* curWeap = Cast<UWeaponComponent>(weapons[i]);
		weaponNameIndexMap.Add(curWeap->GetPriority(), curWeap);
		obtainedWeapons.Add(false);
	}
	UWeaponComponent** tempWeap = weaponNameIndexMap.Find(currentWeaponIndex);
	currentWeapon = *tempWeap;
	obtainedWeapons[currentWeaponIndex] = true;
}

/// Tick override
void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/// Enable acquired weapon from pickup
void UWeaponManagerComponent::AcquireWeapon(FString weaponName) {
	for (auto& pair : weaponNameIndexMap) {
		if (pair.Value->GetName() == weaponName) {
			obtainedWeapons[pair.Key] = true;
			break;
		}
	}
}

/// Switch to next weapon
void UWeaponManagerComponent::CycleNextWeapon()
{
	currentWeaponIndex = (currentWeaponIndex + 1) % numberOfWeapons;
	if (obtainedWeapons[currentWeaponIndex]) {
		currentWeapon = *weaponNameIndexMap.Find(currentWeaponIndex);
		onWeaponChanged.Broadcast(currentWeapon->GetIcon());
	}
	else {
		CycleNextWeapon();
	}
}

/// Switch to previous weapon
void UWeaponManagerComponent::CyclePreviousWeapon()
{
	currentWeaponIndex = (currentWeaponIndex - 1) < 0 ? numberOfWeapons - 1 : currentWeaponIndex - 1;
	if (obtainedWeapons[currentWeaponIndex]) {
		currentWeapon = *weaponNameIndexMap.Find(currentWeaponIndex);
		onWeaponChanged.Broadcast(currentWeapon->GetIcon());
	}
	else {
		CyclePreviousWeapon();
	}
}

/// Fire currently selected weapon
void UWeaponManagerComponent::FireCurrentWeapon(bool toFire)
{
	currentWeapon->SetFiring(toFire);
}

/// Return the currently selected weapon
FString UWeaponManagerComponent::GetCurrentWeapon() const {
	return currentWeapon->GetName();
}