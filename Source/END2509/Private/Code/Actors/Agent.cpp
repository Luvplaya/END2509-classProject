// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "Examples/CodeRifle.h"
#include "BehaviorTree/BlackboardComponent.h"
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

void AAgent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;
    HealthRatio = 1.f;

    UpdateHealthBlackboard();
}

void AAgent::ApplyDamage_Implementation(float Amount)
{
    CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
    HealthRatio = (MaxHealth > 0.f) ? (CurrentHealth / MaxHealth) : 0.f;

    UpdateHealthBlackboard();

    if (CurrentHealth <= 0.f)
    {
        HandleDeath();
    }
}

void AAgent::UpdateHealthBlackboard()
{
    if (UBlackboardComponent* BB = GetBlackboard())
    {
        BB->SetValueAsFloat(TEXT("HealthRatio"), HealthRatio);
    }
}

UBlackboardComponent* AAgent::GetBlackboard() const
{
    if (AAIController* AIC = Cast<AAIController>(GetController()))
    {
        return AIC->GetBlackboardComponent();
    }
    return nullptr;
}

float AAgent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    
    const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent,
        EventInstigator, DamageCauser);

    const float UseDamage = (ActualDamage > 0.f) ? ActualDamage : DamageAmount;
    if (UseDamage <= 0.f)
        return ActualDamage;

   
    CurrentHealth = FMath::Clamp(CurrentHealth - UseDamage, 0.f, MaxHealth);
    HealthRatio = (MaxHealth > 0.f) ? (CurrentHealth / MaxHealth) : 0.f;

    UpdateHealthBlackboard();

    if (CurrentHealth <= 0.f)
    {
        HandleDeath(); 
    }

    return ActualDamage;
}
