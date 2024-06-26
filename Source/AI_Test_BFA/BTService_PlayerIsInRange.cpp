// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerIsInRange.h"

#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Zombie_AIController.h"

UBTService_PlayerIsInRange::UBTService_PlayerIsInRange()
{
	NodeName = TEXT("Update Player Is In Range");
}

void UBTService_PlayerIsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
		return;

	AZombie_AIController* AIController = Cast<AZombie_AIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return;

	bool bPlayerInRange = FVector::Dist(PlayerPawn->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) < AIController->GetMaxPlayerRange();
	AIController->SetIsIdle(!bPlayerInRange);
	if (bPlayerInRange)
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}
