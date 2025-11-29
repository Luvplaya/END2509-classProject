// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleFunctions.h"
#include "../END2509.h"
// Sets default values
AExampleFunctions::AExampleFunctions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleFunctions::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(Game, Error, TEXT("In Begin Play in c++"));
	BlueprintNativeEvent();
	UE_LOG(Game, Warning, TEXT("Just Called Bluprint Native Event in c++, will also trigger in bluprint"));
	BlueprintNativeEvent_Implementation();
	UE_LOG(Game, Warning, TEXT("Just Called Bluprint Native Event_Implementation , will not  trigger blueprint native events in bluprint"));
}

// Called every frame
void AExampleFunctions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleFunctions::BlueprintCallable()
{
	UE_LOG(Game, Log, TEXT("Blueprint Callable"));
}

float AExampleFunctions::PureFuction() const
{
	return 3.14f;
}

void AExampleFunctions::PostLoad()
{
	Super::PostLoad();

}

void AExampleFunctions::BlueprintNativeEvent_Implementation()
{
	UE_LOG(Game, Warning, TEXT("in C++ Blueprint Native Event"));
}

//void AExampleFunctions::BlueprintImplementableEvent()
//{
//	UE_LOG(Game, Log, TEXT("Blueprint Implementable Event"));
//}

