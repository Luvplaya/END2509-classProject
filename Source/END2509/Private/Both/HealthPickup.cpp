// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/HealthPickup.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Both/PickupInterface.h"


AHealthPickup::AHealthPickup()
{
   
    BaseValue = -2.0f;

    if (ParticleComp)
    {
      
        ParticleComp->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
      
        ParticleComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));
       
    }

    if (CollisionComp)
    {
      
        CollisionComp->SetWorldScale3D(FVector(1.5f, 1.5f, 2.0f));
    }
}

bool AHealthPickup::CanPickup(AActor* OtherActor)
{
    if (!OtherActor)
    {
        return false;
    }

    
    if (OtherActor->GetClass()->ImplementsInterface(UPickupInterface::StaticClass()))
    {
       
        return IPickupInterface::Execute_CanPickupHealth(OtherActor, this);
    }

    return false;
}

void AHealthPickup::PostPickup(AActor* OtherActor, const FHitResult& SweepResult)
{
  
    ABasePickup::PostPickup(OtherActor, SweepResult);
}