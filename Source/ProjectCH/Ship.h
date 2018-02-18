// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Ship.generated.h"

#define OUT

/// Ship base class
UCLASS(Blueprintable)
class PROJECTCH_API AShip : public APawn
{
	GENERATED_BODY()

public:
	/// Contructor for this pawn's properties
	AShip();
	/// Tick override
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveLeft();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveRight();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveUp();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveDown();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveForward();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveBack();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveLeft();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveRight();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveUp();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveDown();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveForward();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveBack();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "ShipScore")
	float GetBaseScore() const;
	UFUNCTION(BlueprintCallable, Category = "ShipScore")
	float GetScoreMultiplier() const;

protected:
	/// BeginPlay override or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	float movementSpeed;
	UPROPERTY(EditAnywhere)
	FVector upDirection = FVector::UpVector;
	UPROPERTY(EditAnywhere)
	FVector downDirection = -FVector::UpVector;
	UPROPERTY(EditAnywhere)
	FVector leftDirection = -FVector::RightVector;
	UPROPERTY(EditAnywhere)
	FVector rightDirection = FVector::RightVector;
	UPROPERTY(EditDefaultsOnly)
	float baseScore = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float maxMultiplier = 2.0f;
	UPROPERTY(EditDefaultsOnly)
	float decayTime = 5.0f;
	UPROPERTY(VisibleInstanceOnly)
	float currentMultiplier; 
	UPROPERTY(VisibleInstanceOnly)
	float decayPerSecond;
	FVector currentMovement = FVector::ZeroVector;
	UPrimitiveComponent* primitive = nullptr;
	void Initialize();
	void NormalizeMovementVectors();
	void DecayMultiplier(float DeltaTime);
};
