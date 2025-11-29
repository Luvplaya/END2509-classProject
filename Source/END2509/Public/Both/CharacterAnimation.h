// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */

UCLASS()
class END2509_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit/Death|Debug")
	bool bDebugHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit/Death|Debug")
	bool bDebugDeath = false;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit/Death")
	TObjectPtr<UAnimSequenceBase> HitAsset = nullptr;            

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit/Death")
	TArray<TObjectPtr<UAnimSequenceBase>> DeathAssets;           

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit/Death")
	TObjectPtr<UAnimSequenceBase> CurrentDeathAsset = nullptr;  
           

	

	UFUNCTION(BlueprintCallable, Category = "Hit/Death")
	void HitAnimation(float NotUsed = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Hit/Death")
	void SelectDeathAnimation();

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = Default)
	float Velocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim|Hit/Death")
	FName ActionSlotName = TEXT("ActionSlot");
	   
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
	TObjectPtr<class UAnimSequenceBase> FireAnim = nullptr;

public:
	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();

public:
	UFUNCTION(BlueprintCallable)
	void FireAnimation();
};
