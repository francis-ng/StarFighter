// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Shield.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "ShieldComponent.generated.h"

/// Energy barrier base component
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGHTER_API UShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Contructor for this component's properties
	UShieldComponent();
	/// Tick override
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Shield Component")
	void GenerateShield();

protected:
	/// BeginPlay override
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	FName mountSocketName = NAME_None;
	UPROPERTY(BlueprintReadOnly)
	AShield* theShield = nullptr;

private:	
	UPROPERTY(EditAnywhere)
	float timeToLive = 0.5f;
	UPROPERTY(EditAnywhere)
	float modelScale = 1.0f;
	UPROPERTY(EditAnywhere)
	float cooldown = 1.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AShield> shield = nullptr;
	UWorld* theWorld = nullptr;
	float currentLifetime;
	float currentCooldown;
	void Initialize();
	void CalculateLifetime(float DeltaTime);
	void Cooldown(float DeltaTime);
	void ResetLifetime();
	void ResetCooldown();
};
