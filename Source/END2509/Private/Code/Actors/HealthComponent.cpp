// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


float UHealthComponent::GetHealthRatio() const
{
    return (MaxHealth > 0.f) ? (CurrentHealth / MaxHealth) : 0.f;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = MaxHealth;

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
        UE_LOG(LogTemp, Warning, TEXT("[%s] Health bound. Max=%.1f"), *Owner->GetName(), MaxHealth);
	}
}
void UHealthComponent::HandleTakeAnyDamage(AActor*, float Damage,
    const UDamageType*, AController*, AActor*)

{
    UE_LOG(LogTemp, Warning, TEXT("[Health] %s took %.1f  (%.1f -> %.1f / Max=%.1f)"),
        *GetOwner()->GetName(), Damage, CurrentHealth,
        FMath::Max(0.f, CurrentHealth - Damage), MaxHealth);

    if (Damage == 0.0f || MaxHealth <= 0.0f) return;

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
    const float Ratio = GetHealthRatio();

    if (Damage > 0.0f) 
    {
        if (CurrentHealth > 0.0f)
        {
            UE_LOG(LogTemp, Warning, TEXT("[Health] OnHurt %.2f"), Ratio);
            OnHurt.Broadcast(Ratio);
        }
        else
        {
            if (AActor* Owner = GetOwner())
            {
                Owner->OnTakeAnyDamage.RemoveDynamic(
                    this, &UHealthComponent::HandleTakeAnyDamage);
            }
            UE_LOG(LogTemp, Warning, TEXT("[Health] OnDeath"));
            OnDeath.Broadcast();
        }
    }
    else if (Damage < 0.0f) 
    {
        UE_LOG(LogTemp, Warning, TEXT("[Health] OnHeal %.2f"), Ratio);
        OnHeal.Broadcast(Ratio);
    }
}

