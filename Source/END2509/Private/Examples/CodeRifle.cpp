// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/CodeRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Code/Actors/Projectile.h"
#include "Code/Actors/BasePlayer.h"
#include "Both/PlayerHUD.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include <GameFramework/ProjectileMovementComponent.h>
// Sets default values
ACodeRifle::ACodeRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

    MaxAmmo = 5.0f;       
    CurrentAmmo = MaxAmmo;
}

void ACodeRifle::Attack()
{
    if (!CanShoot() || !ProjectileClass) return;

   

    APawn* ParentPawn = Cast<APawn>(GetParentActor());
    if (!ParentPawn) ParentPawn = Cast<APawn>(GetOwner());
    if (!ParentPawn) return;

    const FVector  SpawnLoc = GetMuzzleWorldLocation();
     FRotator SpawnRot = ParentPawn->GetBaseAimRotation();

    if (APlayerController* PC = Cast<APlayerController>(ParentPawn->GetController()))
    {
        if (ABasePlayer* BP = Cast<ABasePlayer>(ParentPawn))
        {
            if (UPlayerHUD* HUD = BP->GetPlayerHUD())
            {
               const FVector AimAt = HUD->GetDestination(); 
                const FVector Dir = (AimAt - SpawnLoc);
                if (!Dir.IsNearlyZero()) SpawnRot = Dir.Rotation();
                //FlushPersistentDebugLines(GetWorld());
               // DrawDebugLine(GetWorld(), SpawnLoc, AimAt, FColor::Red, false, 0.1f, 0, 1.5f);
               /* DrawDebugPoint(GetWorld(), SpawnLoc, 8.f, FColor::Blue, false, 2.f);
                DrawDebugPoint(GetWorld(), AimAt, 12.f, FColor::Yellow, false, 2.f);
                DrawDebugLine(GetWorld(), SpawnLoc, AimAt, FColor::Green, false, 2.f, 0, 2.f);*/
            }
        }
    }


    FActorSpawnParameters Params;
    Params.Instigator = ParentPawn;
    Params.Owner = ParentPawn->GetController();
   

    AActor*Proj = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLoc, SpawnRot, Params);
    if (Proj)
    {
        if (auto* PMC = Proj->FindComponentByClass<UProjectileMovementComponent>())
        {
            PMC->bRotationFollowsVelocity = true;
            PMC->Velocity = SpawnRot.Vector() * PMC->InitialSpeed; 
        }
    }
    bActionHappening = true;
    GetWorldTimerManager().SetTimer(
        TimerHandle_Reset, this, &ACodeRifle::ActionStopped, ResetTime, false);

    OnRifleAttack.Broadcast();
}

void ACodeRifle::BeginPlay()
{
}

void ACodeRifle::Tick(float DeltaTime)
{
   
}

void ACodeRifle::ActionStopped()
{
    bActionHappening = false;
}

FVector ACodeRifle::GetMuzzleWorldLocation() const
{
    return Mesh->GetSocketLocation(MuzzleSocket);
}

void ACodeRifle::UseAmmo()
{
    CurrentAmmo = FMath::Max(0.f, CurrentAmmo - 1.f);
}

void ACodeRifle::ReloadAmmo()
{
    CurrentAmmo = MaxAmmo;
}

float ACodeRifle::GetAmmoFraction() const
{
    return (MaxAmmo > 0.f) ? (CurrentAmmo / MaxAmmo) : 0.f;
}