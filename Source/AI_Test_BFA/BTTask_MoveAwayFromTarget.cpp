// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAwayFromTarget.h"

#include "BehaviorTree\BlackboardComponent.h"
#include "AIController.h"

UBTTask_MoveAwayFromTarget::UBTTask_MoveAwayFromTarget()
{
	NodeName = TEXT("Move Away From Actor");
}

EBTNodeResult::Type UBTTask_MoveAwayFromTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIController->GetPawn();

	UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	AActor* TargetActor = Cast<AActor>(KeyValue);
	if (TargetActor)
	{
		FVector ToTarget = TargetActor->GetActorLocation() - OwnerPawn->GetActorLocation();

		FVector OppositeDirection = -ToTarget;
		OppositeDirection.Normalize();

		FVector TargetLocation = OwnerPawn->GetActorLocation() + OppositeDirection * 50;
		UE_LOG(LogTemp, Warning, TEXT("Moving t [%f, %f, %f]"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
		AIController->MoveToLocation(TargetLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
