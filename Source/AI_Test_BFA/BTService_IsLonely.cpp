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

	AActor* FarthestFriend = AIController->GetFarthestFriend();
	if (!FarthestFriend)
		return;
	float DistanceToFarthest = FVector::Distance(FarthestFriend->GetActorLocation(), AIController->GetPawn()->GetActorLocation());

	AActor* ClosestFriend = AIController->GetClosestFriend();
	if (!ClosestFriend)
		return;
	float DistanceToClosest = FVector::Distance(ClosestFriend->GetActorLocation(), AIController->GetPawn()->GetActorLocation());

	if (DistanceToClosest > AIController->GetMaxDistanceFromFriends()*2 || DistanceToFarthest > AIController->GetMaxDistanceFromFriends() * 8)
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
}
