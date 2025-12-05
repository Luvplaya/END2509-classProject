// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExamplesDefaultPawn.h"
#include "../END2509.h"
#include "GameFramework/PlayerInput.h"
#include "Examples/ExampleActorWithInterfaces.h"
#include "EngineUtils.h"// TActorIterator(GetActorOfClass)
// Sets default values
AExamplesDefaultPawn::AExamplesDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExamplesDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	//up cast
	AActor* ParentActor = this;
	//down cast
	APawn* ChildPawn = Cast<APawn>(ParentActor);

	if (ChildPawn)
	{
		UE_LOG(Game, Warning, TEXT("Actor is %s"), *ChildPawn->GetName());
	}
	else
	{
		UE_LOG(Game, Log, TEXT("Numbers are %d or %f"), 4, 7.1f);
	}
	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());

	UE_LOG(Game, Error, TEXT("It is: %hs"), true ? "True" : "False");



	//GAR
	for (TActorIterator<AExampleActorWithInterfaces> itr(GetWorld()); itr; ++itr)
	{
		ParentActor = *itr;

		//UExampleInterface* U = Cast< UExampleInterface>(ParentActor);
		//if (U)
		//{
		//	UE_LOG(Game, Log, TEXT("Actor successfully cast to the U interface"));
		//	//U->TestFunction();// did not show up in intellisense, wont compile
		//}
		
		// this is how you should use a c++ interface
		IExampleInterface* I = Cast< IExampleInterface>(ParentActor);
		if (I)
		{
			UE_LOG(Game, Log, TEXT("Actor successfully cast to the I interface"));
			I->TestFunction();
		}
	}


}


// Called every frame
void AExamplesDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AExamplesDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Test_Spawn", EKeys::SpaceBar));
	PlayerInputComponent->BindAction("Test_Spawn", EInputEvent::IE_Pressed, this, &AExamplesDefaultPawn::Spawn);
}

void AExamplesDefaultPawn::Spawn()
{
	FActorSpawnParameters Params;
	Params.Instigator = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(SpawnBlueprintClass, GetActorTransform(), Params); 
}

