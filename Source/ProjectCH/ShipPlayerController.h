// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnPossessedEvent);

UCLASS()
class PROJECTCH_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	AShip* GetControlledShip() const;
	UPROPERTY(BlueprintAssignable)
	FPawnPossessedEvent onPawnPossessed;
};
