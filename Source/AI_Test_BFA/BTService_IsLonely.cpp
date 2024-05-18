// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsLonely.h"
#include "Zombie_AIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UBTService_IsLonely::UBTService_IsLonely()
{
	NodeName = TEXT("Is Lonely ?");
}

void UBTService_IsLonely::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	{
		UE_LOG(LogTemp, Warning, TEXT("No closest friend"));
		return;
	}

	bool isTooClose = FVector::Distance(ClosestFriend->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) > AIController->GetMaxDistanceFromFriends();

	if (isTooClose)
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}
