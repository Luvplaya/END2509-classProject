// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeAgentController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACodeAgentController::ACodeAgentController()
{
    PrimaryActorTick.bCanEverTick = true;
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 9000.f;
    SightConfig->LoseSightRadius = 1100.f;
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
    if (UAIPerceptionComponent* Perception =
        FindComponentByClass<UAIPerceptionComponent>())
    {
        PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ACodeAgentController::OnTargetPerception);
    }
}

void ACodeAgentController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB) return;
    const float Now = GetWorld()->GetTimeSeconds();
    if (Stimulus.WasSuccessfullySensed())
    {
        BB->SetValueAsObject(TEXT("Player"), Actor);
        LastTimeSensedPlayer = Now;
    }
    
}
