// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AmmoPickup.h"
#include "Code/Actors/BasePlayer.h"
#include "Examples/CodeRifle.h"

AAmmoPickup::AAmmoPickup()
{
    
}

bool AAmmoPickup::CanPickup(AActor* OtherActor)
{
  
    return Cast<ABasePlayer>(OtherActor) != nullptr;
}

void AAmmoPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
    ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
    if (!Player)
    {
        return;
    }

    ACodeRifle* Rifle = Player->GetEquippedRifle();
    if (!Rifle)
    {
        return;
    }

    Rifle->IncreaseMaxAmmo(MaxAmmoIncrease);

    if (UPlayerHUD* HUD = Player->GetPlayerHUD()) 
    {
        HUD->SetAmmo(Rifle->GetCurrentAmmo(), Rifle->GetMaxAmmo()); 
    }

    Destroy();
}