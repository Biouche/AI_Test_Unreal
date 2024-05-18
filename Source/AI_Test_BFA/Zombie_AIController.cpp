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

AActor* AZombie_AIController::GetClosestFriend()
{
	float MinDistance = 100000;
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	BlackboardComponent->ClearValue(TEXT("ClosestFriend"));
	BlackboardComponent->ClearValue(TEXT("ClosestFriendLocation"));

	ClosestFriend = nullptr;

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
			ClosestFriend = Friend->GetPawn();
		}
	}

	if (!ClosestFriend)
		return nullptr;

	BlackboardComponent->SetValueAsObject(TEXT("ClosestFriend"), ClosestFriend);
	BlackboardComponent->SetValueAsVector(TEXT("ClosestFriendLocation"), ClosestFriend->GetActorLocation());

	return ClosestFriend;
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
