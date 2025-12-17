// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/Spawner.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Code/Actors/Projectile.h"
#include "Code/Actors/Agent.h"
#include "Both/CodeGameMode.h"



ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionComp);

	
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetGenerateOverlapEvents(true);

	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CollisionComp);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(AgentClass, GetActorLocation(), GetActorRotation());

	if (ACodeGameMode* GM = GetWorld()->GetAuthGameMode<ACodeGameMode>())
	{
		GM->NotifyEnemySpawned(Spawned);
	}

}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASpawner::OnSpawnerOverlap);

	SpawnAgent();
}

void ASpawner::SpawnAgent()
{
	if (!AgentClass) return;

	GetWorld()->SpawnActor<AActor>(
		AgentClass,
		GetActorLocation(),
		GetActorRotation()
	);
}

void ASpawner::OnSpawnerOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawner overlap with: %s"), *GetNameSafe(OtherActor));
	if (!OtherActor) return;


	if (!OtherActor->IsA(AProjectile::StaticClass())) return;

	Health--;
	UE_LOG(LogTemp, Warning, TEXT("Spawner Health now: %d"), Health);
	OtherActor->Destroy(); 

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner destroyed!"));
		if (ACodeGameMode* GM = GetWorld()->GetAuthGameMode<ACodeGameMode>())
		{
			GM->NotifySpawnerDestroyed();
		}

		Destroy();
	}
}