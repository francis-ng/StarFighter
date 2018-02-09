// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"

ABossAIController::ABossAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static::ConstructorHelpers::FObjectFinder<UDataTable> BossInstructionData(TEXT("DataTable'/Game/Data/BossInstructions'"));
	if (BossInstructionData.Object) {
		BossInstructionTable = BossInstructionData.Object;
	}
}

void ABossAIController::BeginPlay() {
	Super::BeginPlay();

	PopulateInstructions();
	Initialize();
}

void ABossAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	TrackTime(DeltaTime);
}

void ABossAIController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);
	controlledShip = Cast<AShip>(InPawn);
	if (!controlledShip) {
		UE_LOG(LogTemp, Error, TEXT("%s cannot find controlled ship"), *GetOwner()->GetName())
		return;
	}
	
	auto weaponList = controlledShip->GetComponentsByClass(UWeaponComponent::StaticClass());
	if (weaponList.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("%s cannot find controlled ship's weapon"), *GetOwner()->GetName())
		return;
	}

	for (auto weaponComponent : weaponList)
	{
		UWeaponComponent* curWeapon = Cast<UWeaponComponent>(weaponComponent);
		weapons.Add(curWeapon->GetPriority(), curWeapon);
	}
}

void ABossAIController::PopulateInstructions() {
	TArray<FBossInstructionData*> outRows;
	BossInstructionTable->GetAllRows<FBossInstructionData>(ContextString, outRows);
	BossInstructions = outRows;
}

void ABossAIController::FireWeapon(int32 weaponNumber, bool toFire) const {
	UWeaponComponent* weapon = weapons.FindRef(weaponNumber);
	if (controlledShip && !controlledShip->IsPendingKillOrUnreachable()) {
		weapon->SetFiring(toFire);
	}
}

void ABossAIController::Initialize() {
	lastInstruction = BossInstructions.Num() - 1;
	ResetInstructionSet();
}

void ABossAIController::ResetInstructionSet() {
	timer = 0;
	currentInstruction = 0;
}

/// Keep track of time and whether to execute the next instruction
/// Keyframe style system of tracking boss instructions with no delay between first and last
void ABossAIController::TrackTime(float DeltaTime) {
	timer += DeltaTime;
	if (currentInstruction <= lastInstruction && BossInstructions.Num() > 0) {
		if (BossInstructions[currentInstruction]->TimePoint) {
			ExecuteInstructions(BossInstructions[currentInstruction]);
			currentInstruction++;
		}
	}
	else if (currentInstruction == lastInstruction) {
		ResetInstructionSet();
	}
}

void ABossAIController::ExecuteInstructions(FBossInstructionData* instructions) {
	ExecuteWeapons(instructions->WeaponsToFire);
}

void ABossAIController::ExecuteWeapons(TArray<int32> weaponsToFire) {
	for (int32 weaponNum : weaponsToFire) {
		int32 trueWeaponNum = abs(weaponNum);
		bool toFire = weaponNum < 0 ? false : true;
		FireWeapon(trueWeaponNum, toFire);
	}
}

FVector ABossAIController::FindNearLocation(AActor* playerShip, float randomRadius, float horizontalSize, float verticalSize, float distanceFromPlayer) {
	if (!controlledShip || !playerShip) return FVector(distanceFromPlayer, 0, 0);
	FVector currentLocation = controlledShip->GetActorLocation();
	FVector playerLocation = playerShip->GetActorLocation();

	float x = playerLocation.X + distanceFromPlayer;
	float y = FMath::Clamp<float>(FMath::FRandRange(-randomRadius, randomRadius) + currentLocation.Y, -horizontalSize, horizontalSize);
	float z = FMath::Clamp<float>(FMath::FRandRange(-randomRadius, randomRadius) + currentLocation.Z, -verticalSize, verticalSize);

	return FVector(x, y, z);
}

void ABossAIController::ClearInstructions() {
	BossInstructions.Empty();
	currentInstruction = 0;
	lastInstruction = 0;
}

AShip* ABossAIController::GetControlledShip() const {
	return controlledShip;
}
