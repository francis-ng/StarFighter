// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Ship.h"
#include "HealthComponent.h"
#include "Shield.h"
#include "PlayerShip.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunctionLibrary.generated.h"

/// Components for time data
USTRUCT(BlueprintType)
struct FTimeComponents {
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Time")
	int32 minutes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Time")
	int32 seconds;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Time")
	int32 milliseconds;
};

/// Helper functions class
UCLASS()
class STARFIGHTER_API UHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UHelperFunctionLibrary(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = "DamageHelpers", meta=(WorldContext = "WorldContextObject"))
	static void DealDamage(UObject* WorldContextObject, AMunition* sourceActor, AActor* hitActor);
	UFUNCTION(BlueprintCallable, Category = "ScoreHelpers", meta = (WorldContext = "WorldContextObject"))
	static float CalculateScore(AShip* destroyedShip, float additionalMultiplier = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "GameTimeHelpers", meta = (WorldContext = "WorldContextObject"))
	static FTimeComponents GameTimeToTime(float GameTime);
	UFUNCTION(BlueprintCallable, Category = "TargetingHelpers", meta = (WorldContext = "WorldContextObject"))
	static AShip* FindNearestEnemy(UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "HealthHelpers", meta = (WorldContext = "WorldContextObject"))
	static float GetHealthAsPercentage(AShip* ship);
	UFUNCTION(BlueprintCallable, Category = "HealthHelpers", meta = (WorldContext = "WorldContextObject"))
	static float GetShieldAsPercentage(AShip* ship);
	UFUNCTION(BlueprintCallable, Category = "BossHelpers", meta = (WorldContext = "WorldContextObject"))
	static bool BossExists(UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "LocalizationHelpers", meta = (WorldContext = "WorldContextObject"))
	static void SetLocale(FString locale);
};
