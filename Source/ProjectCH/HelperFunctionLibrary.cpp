// Francis Ng 2017-2018

#include "HelperFunctionLibrary.h"

/// Constructor
UHelperFunctionLibrary::UHelperFunctionLibrary(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer) {

}

/// Deal damage when an ammunition actor hits another actor
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

/// Calculate the score that should be added on ship destruction
float UHelperFunctionLibrary::CalculateScore(AShip* destroyedShip, float additionalMultiplier) {
	float shipScore = destroyedShip->GetScoreMultiplier() * destroyedShip->GetBaseScore();
	return shipScore * additionalMultiplier;
}

/// Convert the game time to min, sec, and msec
FTimeComponents UHelperFunctionLibrary::GameTimeToTime(float GameTime) {
	FTimeComponents time;
	time.minutes = floor(GameTime / 60);
	time.seconds = floor(GameTime - time.minutes*60);
	time.milliseconds = floor(fmod(GameTime, 1) * 1000);
	return time;
}

/// Find the closest enemy to the player
AShip* UHelperFunctionLibrary::FindNearestEnemy(UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	APawn* playerShip = World->GetFirstPlayerController()->GetPawn();
	if (!playerShip) {
		UE_LOG(LogTemp, Error, TEXT("Cannot find player ship from world"), )
		return nullptr;
	}

	AShip* target = nullptr;
	float minDistance = INT32_MAX;
	for (TActorIterator<AShip> EnemyItr(World); EnemyItr; ++EnemyItr) {
		AShip* ship = *EnemyItr;
		if (ship == playerShip) continue;
		float distance = ship->GetDistanceTo(playerShip);
		if (distance < minDistance) {
			minDistance = distance;
			target = ship;
		}
	}
	return target;
}

/// Find the amount of health a ship has left as a 0-1 float
float UHelperFunctionLibrary::GetHealthAsPercentage(AShip* ship) {
	if (!ship || ship->IsPendingKill()) {
		return 0.0;
	}
	UHealthComponent* health = Cast<UHealthComponent>(ship->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!health) {
		return 0.0;
	}

	return FMath::GetMappedRangeValueClamped(FVector2D(0.0, health->GetMaxHealth()), FVector2D(0.0, 1.0), health->GetCurrentHealth());
}

/// Find the amount of shields a ship has left as a 0-1 float
float UHelperFunctionLibrary::GetShieldAsPercentage(AShip* ship) {
	if (!ship || ship->IsPendingKill()) {
		return 0.0;
	}
	UHealthComponent* health = Cast<UHealthComponent>(ship->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!health) {
		return 0.0;
	}

	return FMath::GetMappedRangeValueClamped(FVector2D(0.0, health->GetMaxShield()), FVector2D(0.0, 1.0), health->GetCurrentShield());
}

/// Check if a boss actor is present in a level
bool UHelperFunctionLibrary::BossExists(UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UClass* BossClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Game/Blueprints/Ships/EnemyBoss.EnemyBoss_C"));
	if (BossClass && World) {
		for (TActorIterator<AShip> EnemyItr(World); EnemyItr; ++EnemyItr) {
			if (EnemyItr->IsA(BossClass)) {
				return true;
			}
		}
	}
	return false;
}