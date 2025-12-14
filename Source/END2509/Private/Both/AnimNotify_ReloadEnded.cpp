// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AnimNotify_ReloadEnded.h"
#include "Both/CharacterAnimation.h"

void UAnimNotify_ReloadEnded::Notify(
    USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation
)
{
    if (!MeshComp) return;

    if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
    {
        Anim->ReloadEnded();
    }
}