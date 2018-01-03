// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Ship.h"
#include "Utilities.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "HomingMissile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCH_API AHomingMissile : public AMunition
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void AcquireTarget() override;
	virtual void InitializeProjectile() override;
	void CalculateNextVector();
	bool IsTargetValid() const;
	UPROPERTY(EditAnywhere)
	float maxForce = 0.0f;
	UPROPERTY()
	APawn* target = nullptr;
	UPROPERTY()
	APawn* playerShip = nullptr;
};
