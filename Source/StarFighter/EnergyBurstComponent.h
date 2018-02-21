// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "HealthComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "EnergyBurstComponent.generated.h"

/// Component for firing the energy burst
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGHTER_API UEnergyBurstComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Contructor for this component's properties
	UEnergyBurstComponent();
	/// Tick override
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetFiring(bool firing);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsFiring() const;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsBursting() const;

protected:
	/// BeginPlay override
	virtual void BeginPlay() override;
	TArray<UActorComponent*> projectileHardpoints;

private:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMunition> projectile = nullptr;
	UPROPERTY(EditAnywhere)
	float burstCooldown = 1;
	UPROPERTY(EditAnywhere)
	FString hardpointTag = "";
	UPROPERTY(EditAnywhere)
	int32 maxBurstCount = 3;
	UPROPERTY(EditAnywhere)
	float maxDamageMultiplier = 10;
	int32 burstCount = 1;
	int32 burstRemaining = 0;
	float burstTimeLeft = 0.0f;
	float damageMultiplier = 1.0f;
	bool isFiring = false;
	bool isBursting = false;
	UWorld* theWorld = nullptr;
	UHealthComponent* healthComponent = nullptr;
	void InitializeWeapon();
	void BurstFire(float DeltaTime);
	void FireWeapon();
	bool CanFire() const;
	void SetBurstStrength();
	void ResetBurstStrength();
};
