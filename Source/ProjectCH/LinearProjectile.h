// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Engine/World.h"
#include "LinearProjectile.generated.h"

/// Fire and forget projectile base class
UCLASS()
class PROJECTCH_API ALinearProjectile : public AMunition
{
	GENERATED_BODY()
	
protected:
	/// BeginPlay override or when spawned
	virtual void BeginPlay() override;
	virtual void AcquireTarget() override;
	virtual void InitializeProjectile() override;
	virtual void SetTargetsPlayer(bool isAimed) override;
	void UpdateLinearVelocity();
};
