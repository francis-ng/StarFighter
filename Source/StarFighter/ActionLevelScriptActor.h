// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "ConstructorHelpers.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "ActionLevelScriptActor.generated.h"

/// Spawn data for a single wave of enemies
USTRUCT(BlueprintType)
struct FWaveDetails : public FTableRowBase {
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Details")
	TSubclassOf<AShip> ShipToSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Details")
	int32 SpawnCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Details")
	FRotator FacingDirection;
};

/// List of ships to spawn to make a wave
USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase {
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Wave")
	float TimePoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Wave")
	TArray<FWaveDetails> WaveDetails;
};

static const FString ContextString(TEXT("GENERAL"));

/// Gameplay level class
UCLASS()
class STARFIGHTER_API AActionLevelScriptActor : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	void BeginPlay() override;
	void PopulateWaves();
	
private:
	UDataTable* WaveDataTable;
	TArray<FWaveData*> WaveData;
	UPROPERTY(EditDefaultsOnly)
	FString DataSheet = TEXT("DataTable'/Game/Data/Level1Waves'");
	UPROPERTY(EditAnywhere)
	float spawnDistance;
	UPROPERTY(EditAnywhere)
	float horizontalLimit;
	UPROPERTY(EditAnywhere)
	float verticalLimit;
	float timer;
	int32 currentInstruction;
	int32 lastInstruction;
	void Initialize();
	void TrackTime(float DeltaTime);
	void ExecuteInstructions(FWaveData* instructions);
	void ResetInstructionSet();
};
