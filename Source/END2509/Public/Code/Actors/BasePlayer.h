// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLost); 
UCLASS()
class END2509_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual bool CanPickupHealth_Implementation(AActor* PickupActor) override;

	
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FinishReload();          

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadEnded();           

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsReloading = false;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadWeapon();

protected:
	UPROPERTY(Category = Character, VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(Category = Character, VisibleAnywhere)
	class UCameraComponent* Camera;
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ACodeRifle> RifleClass;

	UPROPERTY()
	ACodeRifle* EquippedRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UPlayerHUD> HUDClass;

	UPROPERTY()
	UPlayerHUD* PlayerHUD ;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnPlayerLost OnPlayerLost;
public:
	
	virtual void HandleHurt(float Ratio) override;
	virtual void HandleDeath() override;
	
	virtual void HandleHeal(float Ratio) override;
	void PlayerLost();
	UPlayerHUD* GetPlayerHUD() const { return PlayerHUD; }

private:
	UFUNCTION()
	void InputAxisMoveForward(float AxisValue);
	void InputAxisMoveRight(float AxisValue);
	UFUNCTION()
	void OnAttackPressed();
};
