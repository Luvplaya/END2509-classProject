// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/EnemyAttack.h"
#include "AIController.h"
#include "Code/Actors/BaseCharacter.h"
#include "Examples/CodeRifle.h" 

UEnemyAttack::UEnemyAttack()
{
	NodeName = TEXT("Enemy Attack (C++)");
}

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnemyAttack: no AIController"));
        return EBTNodeResult::Failed;
    }

    ABaseCharacter* Agent = Cast<ABaseCharacter>(AIC->GetPawn());
    if (!Agent)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnemyAttack: Pawn is not ABaseCharacter"));
        return EBTNodeResult::Failed;
    }

   
    ACodeRifle* Weapon = Agent->GetWeaponObject();
    if (Weapon && Weapon->CanShoot())
    {
        Weapon->Attack();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BT EnemyAttack: Weapon is invalid or cannot shoot"));
    }


    return EBTNodeResult::Succeeded;
}