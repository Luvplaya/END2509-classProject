// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Examples/CodeRifle.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Both/CharacterAnimation.h"
#include "Code/Actors/HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	//Rotator is used for rotation
	//Ctrl + Shift +Space and arrow keys for override fuction paramater lists
	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponChild"));

	WeaponChild->SetupAttachment(GetMesh(), WeaponSocketName);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	WeaponChild->SetRelativeLocation(FVector::ZeroVector);
	WeaponChild->SetRelativeRotation(FRotator::ZeroRotator);
	WeaponChild->SetRelativeScale3D(FVector(1.f));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponChild && WeaponClass)
	{
		WeaponChild->SetChildActorClass(WeaponClass); 

		
		WeaponObject = Cast<ACodeRifle>(WeaponChild->GetChildActor()); 
	}
	if(USkeletalMeshComponent * Skel = GetMesh())
	{
		AnimBP = Cast<UCharacterAnimation>(Skel->GetAnimInstance());
	}
	if (WeaponObject && AnimBP)
	{
		
		
		WeaponObject->OnRifleAttack.AddDynamic(AnimBP, &UCharacterAnimation::FireAnimation);
		UE_LOG(LogTemp, Warning, TEXT("WeaponObject for %s = %s"),
			*GetName(), *GetNameSafe(WeaponObject));
	}
	if (HealthComponent)
	{
		HealthComponent->OnHurt.AddDynamic(this, &ABaseCharacter::HandleHurt); 
		HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeath);
	}
}

void ABaseCharacter::HandleHurt(float Ratio)
{

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
		{
			Anim->HitAnimation(0.f);
		}
	}
}

void ABaseCharacter::HandleDeath()
{
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
		{
			Anim->SelectDeathAnimation();
		}
	}
	if (AAIController* AIC = Cast<AAIController>(GetController()))
	{
		if (UBrainComponent* Brain = AIC->GetBrainComponent())
		{
			Brain->StopLogic(TEXT("Dead"));
		}

		AIC->StopMovement();
	}

	// Match BP: disable collision so projectiles pass through and AI shoots “over” you
	SetActorEnableCollision(false);

	OwnerDied();
}

void ABaseCharacter::OwnerDied()
{
	if (WeaponObject)
	{
		WeaponObject->SetIsAlive(false);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

