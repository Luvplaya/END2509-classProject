// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GenericTeamAgentInterface.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "CodeAgentController.generated.h"

/**
 * 
 */
class UBehaviorTree;
class UBlackboardComponent;
class UAIPerceptionComponent;
UCLASS()
class END2509_API ACodeAgentController : public AAIController
{
	GENERATED_BODY()
public:
    ACodeAgentController();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;
    virtual FGenericTeamId GetGenericTeamId() const override;
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    
    virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
protected:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float LoseSightDelay = 2.0f;

   
    float LastTimeSensedPlayer = -1.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BTAsset;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UBlackboardComponent* BlackboardComp;
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* PerceptionComp;

    UAISenseConfig_Sight* SightConfig;

    UFUNCTION()
    void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus);
private:
    FGenericTeamId CachedTeamId = FGenericTeamId(0);
};
