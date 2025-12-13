// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AnimNotify_ReloadNow.h"
#include "Both/CharacterAnimation.h"
#include <Code/Actors/BasePlayer.h>


void UAnimNotify_ReloadNow::Notify(
    USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation
)
{
    if (!MeshComp) return;

    if (ABasePlayer* Player = Cast<ABasePlayer>(MeshComp->GetOwner()))
    {
        Player->FinishReload();   
    }
}