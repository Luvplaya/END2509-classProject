// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "EnemyInterface.h"
#include "Agent.generated.h"

/**
 * 
 */
class UBlackboardComponent;
UCLASS()
class END2509_API AAgent : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAgent();
	virtual void Tick(float DeltaSeconds) override;
protected:
    virtual void BeginPlay() override;

    void HandleDeath();

    // Health
    UPROPERTY(EditDefaultsOnly, Category = "Health")
    float MaxHealth = 5.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Health")
    float CurrentHealth = 5.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Health")
    float HealthRatio = 1.0f;

public:
   /* UFUNCTION(BlueprintCallable, Category = "Health")
    void ApplyDamage(float Amount);*/
    virtual void ApplyDamage_Implementation(float Amount) override;

protected:
    void UpdateHealthBlackboard();

    UBlackboardComponent* GetBlackboard() const;
public:
    virtual float TakeDamage(float DamageAmount,
        struct FDamageEvent const& DamageEvent,
        class AController* EventInstigator,
        AActor* DamageCauser) override;
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void ReloadWeapon();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void FinishReload();
};
