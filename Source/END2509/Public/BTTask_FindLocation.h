// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindLocation.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API UBTTask_FindLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindLocation();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Search")
	float Radius = 1000.0f;  

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector LocationKey;
};
