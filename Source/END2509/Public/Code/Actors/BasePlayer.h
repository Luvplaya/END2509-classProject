// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BAseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(Category = Character, VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(Category = Character, VisibleAnywhere)
	class UCameraComponent* Camera;
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	UPlayerHUD* PlayerHUD = nullptr;
public:
	virtual void HandleHurt(float Ratio) override;
	virtual void HandleDeath() override;
	UPlayerHUD* GetPlayerHUD() const { return PlayerHUD; }

private:
	UFUNCTION()
	void InputAxisMoveForward(float AxisValue);
	void InputAxisMoveRight(float AxisValue);
	UFUNCTION()
	void OnAttackPressed();
};
