// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIController.h"

#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "EngineUtils.h"

void AZombie_AIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

	}
}

AActor* AZombie_AIController::GetClosestFriend() const
{
	return ClosestFriend;
}

void AZombie_AIController::FindClosestFriend()
{
	float MinDistance = 100000;
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	APawn* NewClosestFriend = nullptr;
	for (AZombie_AIController* Friend : TActorRange<AZombie_AIController>(GetWorld()))
	{
		if (Friend->GetPawn()->GetName().Equals(GetPawn()->GetName()))
		{
			continue;
		}

		FVector FriendActorLocation = Friend->GetPawn()->GetActorLocation();

		float CurrentActorDistance = FVector::Distance(GetPawn()->GetActorLocation(), FriendActorLocation);

		if (CurrentActorDistance < MinDistance)
		{
			MinDistance = CurrentActorDistance;
			NewClosestFriend = Friend->GetPawn();
		}
	}
	ClosestFriend = NewClosestFriend;
	if (ClosestFriend)
	{
		BlackboardComponent->SetValueAsObject(TEXT("ClosestFriend"), NewClosestFriend);
	}
	else
	{
		BlackboardComponent->ClearValue(TEXT("ClosestFriend"));
	}

}

float AZombie_AIController::GetMinDistanceFromFriends() const
{
	return MinDistanceFromFriends;
}

float AZombie_AIController::GetMaxDistanceFromFriends() const
{
	return MaxDistanceFromFriends;
}

float AZombie_AIController::GetMaxPlayerRange() const
{
	return MaxPlayerRange;
}
