// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Both/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
public:
    AAmmoPickup();

protected:
    virtual bool CanPickup(AActor* OtherActor) override;

    virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
  
    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 MaxAmmoIncrease = 3;
};
