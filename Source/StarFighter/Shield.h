// Francis Ng 2017-2018

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "Munition.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

/// Energy barrier base class
UCLASS()
class STARFIGHTER_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	/// Contructor for this actor's properties
	AShield();
	/// Tick override
	virtual void Tick(float DeltaTime) override;
	void SetPlayerShip(AShip* ship);
	UFUNCTION(BlueprintCallable)
	void ShieldHit(AMunition* hitProjectile);

protected:
	/// BeginPlay override or when spawned
	virtual void BeginPlay() override;

private:	
	AShip* playerShip = nullptr;
	UPROPERTY(EditAnywhere)
	float chargeMultiplier = 1.0f;
};
