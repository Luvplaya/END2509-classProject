// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"

UBTTask_FindLocation::UBTTask_FindLocation()
{
	NodeName = TEXT("Find Location");
}

EBTNodeResult::Type UBTTask_FindLocation::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation FoundLocation;

	
	FVector Origin = Pawn->GetActorLocation();

	
	bool bSuccess = NavSys->GetRandomPointInNavigableRadius(
		Origin,
		Radius,
		FoundLocation
		
	);

	if (!bSuccess)
		return EBTNodeResult::Failed;

	
	BB->SetValueAsVector(LocationKey.SelectedKeyName, FoundLocation.Location);

	return EBTNodeResult::Succeeded;
}
