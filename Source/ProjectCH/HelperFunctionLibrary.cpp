// Fill out your copyright notice in the Description page of Project Settings.

#include "HelperFunctionLibrary.h"

UHelperFunctionLibrary::UHelperFunctionLibrary(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer) {

}

void UHelperFunctionLibrary::DealDamage(UObject* WorldContextObject, AMunition* sourceActor, AActor* hitActor) {
	UHealthComponent* health = Cast<UHealthComponent>(hitActor->GetComponentByClass(UHealthComponent::StaticClass()));
	AShield* shield = Cast<AShield>(hitActor);
	if (health) {
		health->DealDamage(sourceActor->GetDamage());
		APlayerShip* player = Cast<APlayerShip>(hitActor);
		if (player) {
			player->ResetNoDamageMultiplier();
		}
	}
	if (shield) {
		shield->ShieldHit(sourceActor);
	}
}

float UHelperFunctionLibrary::CalculateScore(AShip* destroyedShip, float additionalMultiplier) {
	float shipScore = destroyedShip->GetScoreMultiplier() * destroyedShip->GetBaseScore();
	return shipScore * additionalMultiplier;
}