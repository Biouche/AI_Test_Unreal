// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateClosestFriendLocation.h"

#include "EngineUtils.h"
#include "Zombie_AIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UBTS_UpdateClosestFriendLocation::UBTS_UpdateClosestFriendLocation()
{
	NodeName = TEXT("Update Closest Friend Location");
}

void UBTS_UpdateClosestFriendLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombie_AIController* AIController = Cast<AZombie_AIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast fail"));
		return;
	}

	AIController->FindClosestFriend();
	AIController->FindFarthestFriend();
}
