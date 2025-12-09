// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class UBoxComponent;
class UParticleSystemComponent;

UCLASS(Abstract)
class END2509_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	UBoxComponent* CollisionComp;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	UParticleSystemComponent* ParticleComp;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float BaseValue;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	

	
	virtual bool CanPickup(AActor* OtherActor);

	
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult);

	
	virtual void PostPickup(AActor* OtherActor, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
