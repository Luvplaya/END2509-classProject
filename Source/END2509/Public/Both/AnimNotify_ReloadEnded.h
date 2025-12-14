// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ReloadEnded.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API UAnimNotify_ReloadEnded : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    virtual void Notify(
        USkeletalMeshComponent* MeshComp,
        UAnimSequenceBase* Animation
    ) override;

};
