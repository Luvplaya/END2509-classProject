// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleVariables.h"
#include "../END2509.h"
// Sets default values
AExampleVariables::AExampleVariables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClassType = AExampleVariables::StaticClass();

	ValueArray.Add(3);
	ValueArray.Add(4);
	PointerArray.Add(this);
	PointerArray.Add(nullptr);
}

// Called when the game starts or when spawned
void AExampleVariables::BeginPlay()
{
	Super::BeginPlay();
	EditAnywhere = 500.0f;

	// this is how c++ does the bind in blueprint
	//params send into adddynamic are the same thing as created in blueprint
	//as seen in base character begin play for on rifle attack
	OnDelegateInstance.AddDynamic(this, &AExampleVariables::ExampleBoundFunction);
	OnDelegateInstance.AddDynamic(this, &AExampleVariables::AnotherExampleBoundFunction);
	OnDelegateInstance.Broadcast(this);
	OnDelegateInstance.Broadcast(this);
	OnDelegateInstance.Broadcast(this);
	OnDelegateInstance.Broadcast(this);



}

// Called every frame
void AExampleVariables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleVariables::ExampleBoundFunction(AActor* Other)
{
	UE_LOG(Game, Error, TEXT("Function called by Delegate"));
}

void AExampleVariables::AnotherExampleBoundFunction(AActor* Other)
{
	UE_LOG(Game, Error, TEXT("Another Function called by Delegate"));
}

