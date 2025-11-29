// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class END2509_API AExampleFunctions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();
	//declare in c++, define with blueprint with blueprintimplementableevent
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void BlueprintImplementableEvent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BlueprintNativeEvent();

	UFUNCTION(BlueprintCallable)
	float PureFuction() const;

	virtual void PostLoad() override;

	// multi return values
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MultipleReturnValues(AActor* Actor1, FRotator Rotation, AActor*& Actor2, int32& Index);
};
