// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "Components/InputComponent.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCH_API APlayerShip : public AShip
{
	GENERATED_BODY()
	
public:
	APlayerShip();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
};
