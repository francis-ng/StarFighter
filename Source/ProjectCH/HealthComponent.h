// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthUpdateEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UENUM(BlueprintType)
enum class EDamageLevelEnum : uint8 {
	DL_Healthy UMETA(DisplayName="Healthy"),
	DL_Damaged UMETA(DisplayName="Damaged"),
	DL_Critical UMETA(DisplayName="Critical")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	// Called every frame
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
	FHealthUpdateEvent onShieldUpdate;
	UPROPERTY(BlueprintAssignable)
	FDeathEvent onDeath;

protected:
	// Called when the game starts
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
