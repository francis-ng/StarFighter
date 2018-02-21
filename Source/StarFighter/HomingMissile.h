// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Ship.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "HomingMissile.generated.h"

/// Homing missile base class
UCLASS()
class STARFIGHTER_API AHomingMissile : public AMunition
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	/// BeginPlay override or when spawned
	virtual void BeginPlay() override;
	virtual void AcquireTarget() override;
	virtual void InitializeProjectile() override;
	void CalculateNextVector();
	bool IsTargetValid() const;
	UPROPERTY(EditAnywhere)
	float maxForce = 0.0f;
	UPROPERTY(EditAnywhere)
	float predictionDeltaMod = 1.0;
	UPROPERTY()
	APawn* target = nullptr;
	UPROPERTY()
	APawn* playerShip = nullptr;
};
