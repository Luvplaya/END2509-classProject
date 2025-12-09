// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Both/DamagePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API AHealthPickup : public ADamagePickup
{
	GENERATED_BODY()
	
public:
	AHealthPickup();

protected:
	virtual bool CanPickup(AActor* OtherActor) override;
	virtual void PostPickup(AActor* OtherActor, const FHitResult& SweepResult) override;
};
