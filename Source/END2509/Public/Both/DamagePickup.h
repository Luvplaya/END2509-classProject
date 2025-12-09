// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Both/BasePickup.h"
#include "DamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API ADamagePickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	ADamagePickup();

protected:
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void PostPickup(AActor* OtherActor, const FHitResult& SweepResult) override;
};
