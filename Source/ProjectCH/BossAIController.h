// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ship.h"
#include "WeaponComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "BossAIController.generated.h"

/// Actions for boss at particular point of time
/// There should be a first and last instruction buffer of empty instructions in the instruction array
/// Weapon number is positive to fire, negative to stop firing. Because of that, weapons should be numbered from 1
/// Weapon 0 may always fire
USTRUCT(BlueprintType)
struct FBossInstructionData : public FTableRowBase {
	GENERATED_USTRUCT_BODY();

public:
	FBossInstructionData() :
		TimePoint(0) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Boss Instruction")
	float TimePoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Boss Instruction")
	TArray<int32> WeaponsToFire;
};

static const FString ContextString(TEXT("GENERAL"));
/**
 * 
 */
UCLASS()
class PROJECTCH_API ABossAIController : public AAIController
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* InPawn) override;
	void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Boss AI Controller")
	AShip* GetControlledShip() const;
	UFUNCTION(BlueprintCallable, Category = "Boss AI Controller")
	void FireWeapon(int32 weaponNumber, bool toFire) const;
	UFUNCTION(BlueprintCallable, Category = "Boss AI Controller")
	void ClearInstructions();
	UFUNCTION(BlueprintCallable, Category = "Boss AI Controller")
	FVector FindNearLocation(AActor* playerShip, float randomRadius, float horizontalSize, float verticalSize, float distanceFromPlayer);

	void PopulateInstructions();
	
private:
	AShip* controlledShip = nullptr;
	TMap<int32, UWeaponComponent*> weapons;
	UDataTable* BossInstructionTable;
	TArray<FBossInstructionData*> BossInstructions;
	float timer;
	int32 currentInstruction;
	int32 lastInstruction;
	void Initialize();
	void TrackTime(float DeltaTime);
	void ExecuteInstructions(FBossInstructionData* instructions);
	void ResetInstructionSet();
	void ExecuteWeapons(TArray<int32> weaponsToFire);
};
