// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Examples/CodeRifle.h"            
#include "Both/CharacterAnimation.h" 
#include "Camera/CameraComponent.h" 
#include "GameFramework/PlayerController.h"
#include "Code/Actors/HealthComponent.h"
#include "Both/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
ABasePlayer::ABasePlayer() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0.0f, 80.0f, 90.0f));
	SpringArm->SetupAttachment(GetRootComponent());
	

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind rotation fuctions
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	// space is included in turn right if it is includeed in the project settings
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);
	// bind movement fuctions
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::InputAxisMoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABasePlayer::OnAttackPressed);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PlayerHUDClass)
		{
			PlayerHUD = CreateWidget<UPlayerHUD>(PC, PlayerHUDClass);
			if (PlayerHUD) PlayerHUD->AddToViewport();
		}
	}

	
	if (HealthComponent && PlayerHUD)
	{
		/*HealthComponent->OnHurt.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
		HealthComponent->OnDeath.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);*/
		UE_LOG(LogTemp, Warning, TEXT("HUD bound to HealthComp on %s"), *GetName());
	}
}

void ABasePlayer::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);

	if (UPlayerHUD* HUD = GetPlayerHUD())
	{
		HUD->SetHealth(Ratio);
	}
}

void ABasePlayer::HandleDeath()
{
	Super::HandleDeath();

	if (UPlayerHUD* HUD = GetPlayerHUD())
	{
		HUD->SetHealth(0.0f);
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		DisableInput(PC);
	}
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	FRotator ReturnValue = GetControlRotation();
	float yaw = ReturnValue.Yaw;
	FRotator Rotator = FRotator(0.0f, yaw, 0.0f);
	FVector ForwardVector = Rotator.Vector();
	AddMovementInput(ForwardVector, AxisValue);
}

void ABasePlayer::InputAxisMoveRight(float AxisValue)
{
	FRotator ReturnValue = GetControlRotation();
	float yaw = ReturnValue.Yaw;
	FRotator Rotator = FRotator(0.0f, yaw, 0.0f);
	FVector RightVector = Rotator.RotateVector(FVector::RightVector);
	AddMovementInput(RightVector, AxisValue);
}

void ABasePlayer::OnAttackPressed()
{
	if (WeaponObject) { WeaponObject->Attack(); }
	//if (AnimBP) { AnimBP->FireAnimation(); }
}