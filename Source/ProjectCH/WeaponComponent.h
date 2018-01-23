// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Munition.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "WeaponComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCH_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetFiring(bool firing);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsFiring() const;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsBursting() const;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FString GetName() const;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	int32 GetPriority() const;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UTexture2D* GetIcon() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TArray<UActorComponent*> projectileHardpoints;

private:
	UPROPERTY(EditAnywhere)
	int32 weaponPriority = 0;
	UPROPERTY(EditAnywhere)
	FString weaponName;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMunition> projectile = nullptr;
	UPROPERTY(EditAnywhere)
	float cooldown = 0.2f;
	UPROPERTY(EditAnywhere)
	int32 burstCount = 1;
	UPROPERTY(EditAnywhere)
	float burstCooldown = 1;
	UPROPERTY(EditAnywhere)
	FString hardpointTag = "";
	UPROPERTY(EditAnywhere)
	bool targetsPlayer;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* weaponIcon = nullptr;
	int32 burstRemaining = 0;
	float timeleft = 0.0f;
	float burstTimeLeft = 0.0f;
	bool isFiring = false;
	bool isBursting = false;
	UWorld* theWorld = nullptr;
	void InitializeWeapon();
	void CooldownWeapon(float DeltaTime);
	void BurstFire(float DeltaTime);
	void FireWeapon();
};
