// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "WeaponComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "ShipAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCH_API AShipAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* InPawn) override;
	void BeginPlay() override;
	AShip* GetControlledShip() const;

private:
	AShip* controlledShip = nullptr;
	UWeaponComponent* controlledShipWeapon = nullptr;
};
