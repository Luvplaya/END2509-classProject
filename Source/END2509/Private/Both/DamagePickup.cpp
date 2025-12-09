// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/DamagePickup.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


ADamagePickup::ADamagePickup()
{
   
    BaseValue = 2.f;

    
    if (ParticleComp)
    {
       
        ParticleComp->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
       
        ParticleComp->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));
       
    }

    if (CollisionComp)
    {
       
        CollisionComp->SetWorldScale3D(FVector(1.6f));
    }
}

void ADamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
    if (!OtherActor || BaseValue == 0.f)
    {
        return;
    }

    
    UGameplayStatics::ApplyDamage(
        OtherActor,
        BaseValue,                   
        GetInstigatorController(),
        this,
        nullptr                     
    );
}

void ADamagePickup::PostPickup(AActor* OtherActor, const FHitResult& SweepResult)
{
   
}
