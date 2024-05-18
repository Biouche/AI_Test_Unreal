// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIController.h"

#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "EngineUtils.h"
#include "KillEmAllGameMode.h"

void AZombie_AIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AZombie_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (GetPawn() && BlackboardComponent && !BlackboardComponent->IsVectorValueSet(TEXT("StartLocation")))
	{
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}

	AKillEmAllGameMode* GameMode = GetWorld()->GetAuthGameMode<AKillEmAllGameMode>();
	if (!GameMode)
		return;

	if (GameMode->Enemies.Num() <= GameMode->InitialEnemiesCount / 2)
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsHalfEnemiesLeft"), true);
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

	AKillEmAllGameMode* GameMode = GetWorld()->GetAuthGameMode<AKillEmAllGameMode>();
	if (!GameMode)
		return;

	APawn* NewClosestFriend = nullptr;
	for (AZombie_AIController* Friend : GameMode->Enemies)
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
