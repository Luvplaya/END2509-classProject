// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;

  
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
    CollisionComp->SetGenerateOverlapEvents(true);

   
    ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
    ParticleComp->SetupAttachment(RootComponent);

   
    BaseValue = 0.f;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
    if (CollisionComp)
    {
        CollisionComp->OnComponentBeginOverlap.AddDynamic(
            this, &ABasePickup::OnOverlap);
    }
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABasePickup::OnOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

   
    if (CanPickup(OtherActor))
    {
      
        HandlePickup(OtherActor, SweepResult);
       
        PostPickup(OtherActor, SweepResult);
    }
}



bool ABasePickup::CanPickup(AActor* OtherActor)
{
   
    return true;
}

void ABasePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
    
}

void ABasePickup::PostPickup(AActor* OtherActor, const FHitResult& SweepResult)
{
    
    Destroy();
}
