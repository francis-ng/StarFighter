// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Munition.generated.h"

UCLASS()
class PROJECTCH_API AMunition : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMunition();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	void SetInitialDirection(FVector direction);
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	virtual void SetTargetsPlayer(bool isAimed);
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	float GetDamage() const;

protected:
	UPROPERTY(EditAnywhere)
	float maxSpeed = 0.0f;
	UPROPERTY(EditAnywhere)
	float initialSpeed = 0.0f;
	UPROPERTY(EditAnywhere)
	float damage = 0.0f;
	UPROPERTY(EditAnywhere)
	bool targetsPlayer = false;
	UPROPERTY(EditAnywhere)
	float timeToLive = 0.0f;
	UPROPERTY(EditAnywhere)
	float modelScale = 1.0f;
	UPROPERTY(EditAnywhere)
	FVector initialDirection;
	UPrimitiveComponent* primitive;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CalculateLifetime(float DeltaTime);
	virtual void AcquireTarget();
	virtual void InitializeProjectile();
};
