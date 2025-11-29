// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Agent.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API AAgent : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAgent();
	virtual void Tick(float DeltaSeconds) override;
	
};
