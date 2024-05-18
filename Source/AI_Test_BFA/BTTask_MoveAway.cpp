// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAway.h"


#include "BehaviorTree\BlackboardComponent.h"
#include "AIController.h"

UBTTask_MoveAway::UBTTask_MoveAway()
{
	NodeName = TEXT("Move Away From");
}

EBTNodeResult::Type UBTTask_MoveAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();

	UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	AActor* TargetActor = Cast<AActor>(KeyValue);
	if (TargetActor)
	{
		AIController->MoveToActor(TargetActor, AcceptableRadius, true, true, bAllowStrafe, FilterClass);
	}

	return EBTNodeResult::Succeeded;
}
