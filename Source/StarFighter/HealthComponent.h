// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthUpdateEvent, float, MaxHealth, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FEnergyUpdateEvent, float, MaxShield, float, CurrentShield, float, MaxOvercharge, float, CurrentOvercharge);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

/// Health stage enums
UENUM(BlueprintType)
enum class EDamageLevelEnum : uint8 {
	DL_Healthy UMETA(DisplayName="Healthy"),
	DL_Damaged UMETA(DisplayName="Damaged"),
	DL_Critical UMETA(DisplayName="Critical")
};

/// Health component class
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGHTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Contructor for this component's properties
	UHealthComponent();
	/// Tick override
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetMaxShield() const;
	UFUNCTION(BlueprintCallable, Category="HealthComponent")
	float GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetCurrentShield() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetMaxOvercharge() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetOvercharge() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float GetTotalEnergy() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void DealDamage(float damage);
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void RecoverHealth(float amount);
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void RecoverShield(float amount);
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void Overcharge(float amount);
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	float EnergyRelease();
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	EDamageLevelEnum GetDamageLevel() const;
	UPROPERTY(BlueprintAssignable)
	FHealthUpdateEvent onHealthUpdate;
	UPROPERTY(BlueprintAssignable)
	FEnergyUpdateEvent onShieldUpdate;
	UPROPERTY(BlueprintAssignable)
	FDeathEvent onDeath;

protected:
	/// BeginPlay override
	virtual void BeginPlay() override;

private:	
	float currentHealth, currentShield, shieldOvercharge;
	UPROPERTY(EditAnywhere)
	float maxHealth = 0.0f;
	UPROPERTY(EditAnywhere)
	float maxShield = 0.0f;
	UPROPERTY(EditAnywhere)
	float shieldRechargeRate = 0.0f;
	UPROPERTY(EditAnywhere)
	float maxOverchargeMultiplier = 2.0f;
	UPROPERTY(EditAnywhere)
	float damagedHealthPercentage = 0.5f;
	UPROPERTY(EditAnywhere)
	float criticalHealthPercentage = 0.25f;
};
