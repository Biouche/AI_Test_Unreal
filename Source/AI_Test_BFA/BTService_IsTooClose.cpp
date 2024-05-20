// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsTooClose.h"
#include "Zombie_AIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UBTService_IsTooClose::UBTService_IsTooClose()
{
	NodeName = TEXT("Is Too Close ?");
}

void UBTService_IsTooClose::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombie_AIController* AIController = Cast<AZombie_AIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast fail"));
		return;
	}

	AActor* ClosestFriend = AIController->GetClosestFriend();
	if (!ClosestFriend)
		return;

	bool bIsTooClose = FVector::Distance(ClosestFriend->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) < AIController->GetMinDistanceFromFriends();

	if (bIsTooClose)
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
}
