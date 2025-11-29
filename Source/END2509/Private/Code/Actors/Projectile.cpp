// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../END2509.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Code/Actors/HealthComponent.h"

// Sets default values
AProjectile::AProjectile():Size(0.18f,0.18f,0.18f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(SphereCollider);
	SphereCollider->SetWorldScale3D(Size);
	
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap); 
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("No Collision");
	SphereMesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	SphereMesh->SetStaticMesh(Asset.Object);
	SphereMesh->SetupAttachment(SphereCollider);
	
	SphereCollider->OnComponentHit.AddDynamic(this, &AProjectile::HandleHit);
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1900;
	ProjectileMovement->MaxSpeed = 1900;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(
		TimerHandle_Life,
		this,
		&AProjectile::OnLifeExpired,
		DestroyTime,
		false
	);
	if (APawn* P = GetInstigator())             
		OwnerController = P->GetController();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	UE_LOG(Game, Warning, TEXT("Hit was Called"));
	UE_LOG(Game, Error,TEXT("Other Actor Name is: %s"), *OtherActor->GetName());
	Destroy();
}
void AProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor == GetInstigator()) return;

	
	if (OtherActor->GetOwner() == GetInstigator()) return;
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlapped %s"), *OtherActor->GetName());
	if (OtherActor->FindComponentByClass<UHealthComponent>())    
	{
		const float DamageAmount = Damage;
		UGameplayStatics::ApplyDamage(
			OtherActor, Damage,
			OwnerController,
			this,
			UDamageType::StaticClass()
		);
		UE_LOG(LogTemp, Warning, TEXT("ApplyDamage(%.1f) on %s (CanBeDamaged=%s)"),
			Damage, *OtherActor->GetName(),
			OtherActor->CanBeDamaged() ? TEXT("true") : TEXT("false"));
		Destroy();
	}
}

void AProjectile::OnLifeExpired()
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile timed out (DestroyTime = %.2f)"), DestroyTime);
	Destroy();
}
