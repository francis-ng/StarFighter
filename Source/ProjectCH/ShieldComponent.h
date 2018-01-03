// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shield.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "ShieldComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCH_API UShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShieldComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Shield Component")
	void GenerateShield();

protected:
	// Called when the game starts
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
