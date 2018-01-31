// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionLevelScriptActor.h"

AActionLevelScriptActor::AActionLevelScriptActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static::ConstructorHelpers::FObjectFinder<UDataTable> WaveDataObject(*DataSheet);
	if (WaveDataObject.Object) {
		WaveDataTable = WaveDataObject.Object;
	}
}

void AActionLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	PopulateWaves();
	Initialize();
}

void AActionLevelScriptActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	TrackTime(DeltaTime);
}

void AActionLevelScriptActor::Initialize() {
	lastInstruction = WaveData.Num() - 1;
	ResetInstructionSet();
}

void AActionLevelScriptActor::PopulateWaves() {
	TArray<FWaveData*> outRows;
	WaveDataTable->GetAllRows<FWaveData>(ContextString, outRows);
	WaveData = outRows;
}

void AActionLevelScriptActor::TrackTime(float DeltaTime) {
	timer += DeltaTime;
	if (currentInstruction <= lastInstruction) {
		if (timer >= WaveData[currentInstruction]->TimePoint) {
			ExecuteInstructions(WaveData[currentInstruction]);
			currentInstruction++;
		}
	}
}

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

void AActionLevelScriptActor::ResetInstructionSet() {
	timer = 0;
	currentInstruction = 0;
}