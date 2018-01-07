// Fill out your copyright notice in the Description page of Project Settings.

#include "Shield.h"


// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShield::SetPlayerShip(AShip* ship) {
	playerShip = ship;
}

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