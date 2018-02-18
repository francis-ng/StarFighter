// Francis Ng 2017-2018

#include "ShieldComponent.h"


/// Contructor for this component's properties
UShieldComponent::UShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


/// BeginPlay override
void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}


/// Tick override
void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (theShield) {
		CalculateLifetime(DeltaTime);
	}
	else {
		Cooldown(DeltaTime);
	}
}

/// Spawn barrier if available and attach to parent
void UShieldComponent::GenerateShield() {
	AActor* parentActor = GetOwner();
	if (!theShield && currentCooldown <= 0) {
		theShield = Cast<AShield>(theWorld->SpawnActor(shield, &FTransform::Identity));
		theShield->SetPlayerShip(Cast<AShip>(GetOwner()));
		theShield->SetActorScale3D(FVector(modelScale, modelScale, modelScale));
		theShield->AttachToActor(parentActor, FAttachmentTransformRules::KeepRelativeTransform, mountSocketName);
	}
}

/// Calculate the amount of time left before despawn
void UShieldComponent::CalculateLifetime(float DeltaTime) {
	currentLifetime -= DeltaTime;
	if (currentLifetime <= 0) {
		theShield->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		if (!theShield->Destroy()) {
			UE_LOG(LogTemp, Warning, TEXT("%s cannot be destroyed"), *theShield->GetName())
		}
		theShield = nullptr;
		ResetLifetime();
		ResetCooldown();
	}
}

/// Reset lifetime counter
void UShieldComponent::ResetLifetime() {
	currentLifetime = timeToLive;
}

/// Cooldown barrier
void UShieldComponent::Cooldown(float DeltaTime) {
	currentCooldown -= DeltaTime;
}

/// Reset cooldown counter
void UShieldComponent::ResetCooldown() {
	currentCooldown = cooldown;
}

/// Initialization
void UShieldComponent::Initialize() {
	if (!shield) {
		UE_LOG(LogTemp, Error, TEXT("No shield set on %s"), *GetOwner()->GetName())
	}

	if (mountSocketName == NAME_None) {
		UE_LOG(LogTemp, Error, TEXT("No shield mount socket on %s"), *GetOwner()->GetName())
	}

	theWorld = GetWorld();
	if (!theWorld) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get world"))
	}

	ResetLifetime();
}