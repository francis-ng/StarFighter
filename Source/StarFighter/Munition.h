// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Munition.generated.h"

/// Ammunition base class
UCLASS()
class STARFIGHTER_API AMunition : public APawn
{
	GENERATED_BODY()

public:
	/// Contructor for this pawn's properties
	AMunition();
	/// Tick override
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	void SetInitialDirection(FVector direction);
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	virtual void SetTargetsPlayer(bool isAimed);
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	float GetDamage() const;
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	float GetDamageMultiplier() const;
	UFUNCTION(BlueprintCallable, Category = "Munitions")
	void SetDamageMultiplier(float multiplier);

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
	FVector initialDirection;
	float damageMultiplier = 1.0f;
	UPrimitiveComponent* primitive;
	/// BeginPlay override or when spawned
	virtual void BeginPlay() override;
	void CalculateLifetime(float DeltaTime);
	virtual void AcquireTarget();
	virtual void InitializeProjectile();
	void TurnToDirectionOfMovement();
};
