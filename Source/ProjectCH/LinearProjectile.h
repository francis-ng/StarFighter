// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Engine/World.h"
#include "LinearProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCH_API ALinearProjectile : public AMunition
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void AcquireTarget() override;
	virtual void InitializeProjectile() override;
	virtual void SetTargetsPlayer(bool isAimed) override;
	void UpdateLinearVelocity();
};
