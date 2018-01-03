// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "Munition.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class PROJECTCH_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetPlayerShip(AShip* ship);
	UFUNCTION(BlueprintCallable)
	void ShieldHit(AMunition* hitProjectile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	AShip* playerShip = nullptr;
	UPROPERTY(EditAnywhere)
	float chargeMultiplier = 1.0f;
};
