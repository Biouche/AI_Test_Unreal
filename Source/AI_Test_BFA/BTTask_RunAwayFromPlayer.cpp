// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunAwayFromPlayer.h"

#include "Kismet\GameplayStatics.h"
#include "AIController.h"

#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"

UBTTask_RunAwayFromPlayer::UBTTask_RunAwayFromPlayer()
{
	NodeName = TEXT("Move Away From Player");
}

EBTNodeResult::Type UBTTask_RunAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner())
		return EBTNodeResult::Failed;

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIController->GetPawn();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
		EBTNodeResult::Failed;

	// Determine if enemy is MoveAwayDistance from the player to trigger run away behavior.
	if (FVector::Dist(PlayerPawn->GetActorLocation(), OwnerPawn->GetActorLocation()) < MoveAwayDistance)
	{
		FVector OppositeDirection = PlayerPawn->GetActorForwardVector();
		OppositeDirection.Normalize();

		FVector TargetLocation = OwnerPawn->GetActorLocation() + OppositeDirection * MoveAwayDistance;

		AIController->MoveToLocation(TargetLocation);
	}

	return EBTNodeResult::Succeeded;
}
