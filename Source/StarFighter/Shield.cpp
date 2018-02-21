// Francis Ng 2017-2018

#include "Shield.h"


/// Contructor
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/// BeginPlay override or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

/// Tick override
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/// Store the player controlled ship in variable
void AShield::SetPlayerShip(AShip* ship) {
	playerShip = ship;
}

/// Charge shields when barrier is hit
void AShield::ShieldHit(AMunition* hitProjectile) {
	if (playerShip) {
		UHealthComponent* health = Cast<UHealthComponent>(playerShip->GetComponentByClass(UHealthComponent::StaticClass()));
		if (!health) {
			UE_LOG(LogTemp, Error, TEXT("Player missing health component"))
		}
		float damage = hitProjectile->GetDamage();
		health->Overcharge(damage * chargeMultiplier);
	}
}