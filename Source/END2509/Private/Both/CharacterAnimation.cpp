// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include <Code/Actors/BasePlayer.h>
#include "Animation/AnimInstance.h" 

void UCharacterAnimation::HitAnimation(float/*NotUsed*/)
{
	if (HitAsset)
	{
		PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
	}
}
void UCharacterAnimation::SelectDeathAnimation()
{
	if (DeathAssets.Num() > 0)
	{
		const int32 Index = FMath::RandRange(0, DeathAssets.Num() - 1);
		CurrentDeathAsset = DeathAssets[Index];
		
	}
}
void UCharacterAnimation::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	PreviewWindowUpdate();
	APawn* Pawn = TryGetPawnOwner(); 
	if (Pawn)
	{
		//is valid
		Velocity = Pawn->GetVelocity().Length();
		
		const FVector  Vel = Pawn->GetVelocity();
		const FRotator BaseRot = Pawn->GetActorRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection(Vel, BaseRot);
	}
	else 
	{
      //not valid

	}
}

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
	if (bDebugDeath)
	{
		SelectDeathAnimation();
		bDebugDeath = false;
		return;
	}

	if (bDebugHit)
	{
		HitAnimation(0.f);
		bDebugHit = false;
	}
}

void UCharacterAnimation::FireAnimation()
{
	if (FireAnim)
	{
		PlaySlotAnimationAsDynamicMontage(
			FireAnim, ActionSlotName,
			/*BlendIn*/ 0.10f, /*BlendOut*/ 0.10f,
			/*Rate*/ 1.f, /*Loops*/ 1, /*BlendOutTrigger*/ 0.f);
	}
}

void UCharacterAnimation::ReloadAnimation()
{
	if (ReloadAsset)   
	{
		PlaySlotAnimationAsDynamicMontage(
			ReloadAsset,
			ActionSlotName,
			0.1f, 0.1f, 1.f, 1, 0.f);
	}
	bIsReloading = true;
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
}
void UCharacterAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	
	OnReloadNow.AddDynamic(this, &UCharacterAnimation::ReloadNow);
	OnReloadEnded.AddDynamic(this, &UCharacterAnimation::ReloadFinished);
}
void UCharacterAnimation::ReloadNow()
{
	APawn* OwnerPawn = TryGetPawnOwner();
	if (ABasePlayer* Player = Cast<ABasePlayer>(OwnerPawn))
	{
		Player->FinishReload();
	}
}

void UCharacterAnimation::ReloadFinished()
{
	APawn* OwnerPawn = TryGetPawnOwner();
	if (ABasePlayer* Player = Cast<ABasePlayer>(OwnerPawn))
	{
		Player->ReloadEnded();
	}
}