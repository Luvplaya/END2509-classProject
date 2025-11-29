// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeRifle.generated.h"


class USkeletalMeshComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRifleAttack);

UCLASS()
class END2509_API ACodeRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeRifle();
	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintPure) bool CanShoot() const { return !bActionHappening&& bIsAlive; }
	UFUNCTION(BlueprintCallable)
	void SetIsAlive(bool bInAlive) { bIsAlive = bInAlive; }
	
	UPROPERTY(BlueprintAssignable) FOnRifleAttack OnRifleAttack;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rifle")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Rifle")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Rifle")
	FName MuzzleSocket = TEXT("MuzzleFlashSocket");

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Timing") float ResetTime = 2.0f;

	UFUNCTION() void ActionStopped();
	
	UPROPERTY(VisibleAnywhere, Category = "Fire|State")
	bool bActionHappening = false;
	FTimerHandle TimerHandle_Reset;
	
	UPROPERTY(EditAnywhere, Category = "Fire|State")
	bool bIsAlive = true;
	
	
	FVector GetMuzzleWorldLocation() const;

};
