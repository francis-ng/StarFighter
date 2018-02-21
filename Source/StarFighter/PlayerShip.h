// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "Components/InputComponent.h"
#include "PlayerShip.generated.h"

/// Multiplier update broadcast delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplierUpdateEvent, float, Multiplier);

/// Player ship base class
UCLASS()
class STARFIGHTER_API APlayerShip : public AShip
{
	GENERATED_BODY()
	
public:
	APlayerShip();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "PlayerShipMultiplier")
	float GetNoDamageMultiplier() const;
	UFUNCTION(BlueprintCallable, Category = "PlayerShipMultiplier")
	void ResetNoDamageMultiplier();
	UPROPERTY(BlueprintAssignable)
	FMultiplierUpdateEvent onNoDamageMultiplierUpdate;

private:
	UPROPERTY(EditDefaultsOnly)
	float noDamageMultiplierIncrement = 0.1f;
	UPROPERTY(EditDefaultsOnly)
	float noDamageMultiplierTimestep = 1.0f;
	UPROPERTY(VisibleInstanceOnly)
	float currentNoDamageMultiplier = 1.0f;
	float timePassed = 0.0f;
	void IncrementNoDamageMultiplier(float DeltaTime);
};
