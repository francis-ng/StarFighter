// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

/// Pawn possessed event delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnPossessedEvent);

/// Ship player controller base class
UCLASS()
class STARFIGHTER_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	AShip* GetControlledShip() const;
	UPROPERTY(BlueprintAssignable)
	FPawnPossessedEvent onPawnPossessed;
};
