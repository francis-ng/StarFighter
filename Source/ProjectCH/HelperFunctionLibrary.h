// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Ship.h"
#include "HealthComponent.h"
#include "Shield.h"
#include "PlayerShip.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCH_API UHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UHelperFunctionLibrary(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = "DamageHelperFunctions", meta=(WorldContext = "WorldContextObject"))
	static void DealDamage(UObject* WorldContextObject, AMunition* sourceActor, AActor* hitActor);
	UFUNCTION(BlueprintCallable, Category = "ScoreHelperFunctions", meta = (WorldContext = "WorldContextObject"))
	static float CalculateScore(AShip* destroyedShip, float additionalMultiplier = 1.0f);
};
