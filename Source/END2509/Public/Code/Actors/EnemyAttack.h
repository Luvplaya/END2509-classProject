// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API UEnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
    UEnemyAttack();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory) override;
};
