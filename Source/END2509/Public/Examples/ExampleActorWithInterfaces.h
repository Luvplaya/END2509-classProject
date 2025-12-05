// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Examples/ExampleInterface.h"

#include "GameFramework/Actor.h"
#include "ExampleActorWithInterfaces.generated.h"

UCLASS()
class END2509_API AExampleActorWithInterfaces : public AActor,
	public IExampleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleActorWithInterfaces();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//----------------------------------------------------------------------//
	// IExampleInterface
	//----------------------------------------------------------------------//
	virtual void TestFunction() override;
};
