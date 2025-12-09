// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Both/CharacterAnimation.h"
#include "Both/PickupInterface.h"
#include "BaseCharacter.generated.h"

class UChildActorComponent;
class ACodeRifle;
class UCharacterAnimation;
class UHealthComponent;

UCLASS(ABSTRACT)
class END2509_API ABaseCharacter : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	virtual bool CanPickup_Implementation(AActor* PickupActor) override;
	virtual bool CanPickupHealth_Implementation(AActor* PickupActor) override;
public:
	FORCEINLINE ACodeRifle* GetWeaponObject() const { return WeaponObject; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UChildActorComponent* WeaponChild;

	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> WeaponClass;

	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = TEXT("WeaponSocket");

	UPROPERTY(Transient) ACodeRifle* WeaponObject = nullptr;
	UPROPERTY(Transient) UCharacterAnimation* AnimBP = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent = nullptr;
	UFUNCTION()
	virtual void HandleHurt(float Ratio);
	UFUNCTION()
	virtual void HandleHeal(float Ratio);
	UFUNCTION()
	virtual void HandleDeath();

	UFUNCTION(BlueprintCallable)
	virtual void OwnerDied();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
