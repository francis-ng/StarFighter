// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponChangedEvent, UTexture2D*, Texture);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCH_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "WeaponManager")
	void CycleNextWeapon();
	UFUNCTION(BlueprintCallable, Category = "WeaponManager")
	void CyclePreviousWeapon();
	UFUNCTION(BlueprintCallable, Category = "WeaponManager")
	void FireCurrentWeapon(bool toFire);
	UFUNCTION(BlueprintCallable, Category = "WeaponManager")
	void AcquireWeapon(FString weaponName);
	UFUNCTION(BlueprintCallable, Category = "WeaponManager")
	FString GetCurrentWeapon() const;
	UPROPERTY(BlueprintAssignable)
	FWeaponChangedEvent onWeaponChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	TArray<bool> obtainedWeapons;
	TMap<int32, UWeaponComponent*> weaponNameIndexMap;
	int32 numberOfWeapons = 0;
	int32 currentWeaponIndex = 0;
	UWeaponComponent* currentWeapon = nullptr;
	void InitializeWeaponManager();
};
