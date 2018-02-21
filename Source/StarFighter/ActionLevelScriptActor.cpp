// Francis Ng 2017-2018

#include "ActionLevelScriptActor.h"

/// Constructor
AActionLevelScriptActor::AActionLevelScriptActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static::ConstructorHelpers::FObjectFinder<UDataTable> WaveDataObject(*DataSheet);
	if (WaveDataObject.Object) {
		WaveDataTable = WaveDataObject.Object;
	}
}

/// BeginPlay override
void AActionLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	PopulateWaves();
	Initialize();
}

/// Tick override
void AActionLevelScriptActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	TrackTime(DeltaTime);
}

/// Initialization function calls
void AActionLevelScriptActor::Initialize() {
	lastInstruction = WaveData.Num() - 1;
	ResetInstructionSet();
}

/// Load datatable and store in variable
void AActionLevelScriptActor::PopulateWaves() {
	TArray<FWaveData*> outRows;
	WaveDataTable->GetAllRows<FWaveData>(ContextString, outRows);
	WaveData = outRows;
}

/// Tick timer and spawn waves if required
void AActionLevelScriptActor::TrackTime(float DeltaTime) {
	timer += DeltaTime;
	if (currentInstruction <= lastInstruction) {
		if (timer >= WaveData[currentInstruction]->TimePoint) {
			ExecuteInstructions(WaveData[currentInstruction]);
			currentInstruction++;
		}
	}
}

/// Execute a set of wave instructions
void AActionLevelScriptActor::ExecuteInstructions(FWaveData* instructions) {
	for (FWaveDetails waveDetail : instructions->WaveDetails) {
		for (int32 i = 0; i < waveDetail.SpawnCount; i++) {
			const FVector randomLocation = FVector(spawnDistance, FMath::RandRange(-horizontalLimit, horizontalLimit), FMath::RandRange(-verticalLimit, verticalLimit));
			GetWorld()->SpawnActor(waveDetail.ShipToSpawn, 
				&randomLocation,
				&waveDetail.FacingDirection);
		}
	}
}

/// Reset timer and wave progression
void AActionLevelScriptActor::ResetInstructionSet() {
	timer = 0;
	currentInstruction = 0;
}