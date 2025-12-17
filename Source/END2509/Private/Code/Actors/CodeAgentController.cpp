// Fill out your copyright notice in the Description page of Project Settings.

#include "Code/Actors/BaseCharacter.h"
#include "Code/Actors/CodeAgentController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACodeAgentController::ACodeAgentController()
{
    PrimaryActorTick.bCanEverTick = true;
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 900.f;
    SightConfig->LoseSightRadius = 1000.f;
    SightConfig->PeripheralVisionAngleDegrees = 45.f;

    PerceptionComp->ConfigureSense(*SightConfig);
    PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}


void ACodeAgentController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (!BTAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("CodeAgentController: BTAsset is null"));
        return;
    }

    
    if (UseBlackboard(BTAsset->BlackboardAsset, BlackboardComp))
    {
        RunBehaviorTree(BTAsset);

        
        if (BlackboardComp)
        {
            BlackboardComp->SetValueAsObject(TEXT("SelfActor"), InPawn);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CodeAgentController: UseBlackboard failed"));
    }
}

void ACodeAgentController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!BlackboardComp)
        return;

    
    if (LastTimeSensedPlayer > 0.f)
    {
        const float TimeSinceSeen =
            GetWorld()->GetTimeSeconds() - LastTimeSensedPlayer;

        if (TimeSinceSeen > LoseSightDelay)
        {
            
            BlackboardComp->ClearValue(TEXT("Player"));
            LastTimeSensedPlayer = -1.f;
        }
    }
}

void ACodeAgentController::BeginPlay()
{
    Super::BeginPlay();
    if (PerceptionComp)
    {
        PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
            this, &ACodeAgentController::OnTargetPerception);
    }
}

void ACodeAgentController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB) return;
   
    const float Now = GetWorld()->GetTimeSeconds();
    if (GetTeamAttitudeTowards(*Actor) != ETeamAttitude::Hostile)
    {
        return; 
    }
    if (Stimulus.WasSuccessfullySensed())
    {
        BB->SetValueAsObject(TEXT("Player"), Actor);
        LastTimeSensedPlayer = Now;
    }
    else
    {
       
        LastTimeSensedPlayer = Now;
    }
}
FGenericTeamId ACodeAgentController::GetGenericTeamId() const
{
   
    if (const ABaseCharacter* BC = Cast<ABaseCharacter>(GetPawn()))
    {
        return BC->GetGenericTeamId();
    }
    return CachedTeamId;
}

void ACodeAgentController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
    CachedTeamId = NewTeamID;
}
ETeamAttitude::Type ACodeAgentController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const ABaseCharacter* Me = Cast<ABaseCharacter>(GetPawn());
    const ABaseCharacter* Them = Cast<ABaseCharacter>(&Other);

    if (!Me || !Them) return ETeamAttitude::Neutral;

    return (Me->GetGenericTeamId() == Them->GetGenericTeamId())
        ? ETeamAttitude::Friendly
        : ETeamAttitude::Hostile;
}