// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "Examples/CodeRifle.h"
AAgent::AAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAgent::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!WeaponObject) return;                
    if (WeaponObject->CanShoot())             
    {
        WeaponObject->Attack();
    }
}
