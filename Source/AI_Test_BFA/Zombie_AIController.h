// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_TEST_BFA_API AZombie_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombie_AIController(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	AActor* GetClosestFriend() const;
	AActor* GetFarthestFriend() const;

	void FindClosestFriend();
	void FindFarthestFriend();

	float GetMaxDistanceFromFriends() const;
	float GetMaxPlayerRange() const;

	bool GetIsIdle() const;
	void SetIsIdle(bool IsIdle);

private:

	UPROPERTY(VisibleAnywhere)
	float DistanceToClosestFriend;

	UPROPERTY(EditAnywhere)
	float CapsuleRadiusOffset = 30;

	UPROPERTY(EditAnywhere)
	float MaxDistanceFromFriends = 200;

	UPROPERTY(EditAnywhere)
	float MaxPlayerRange = 10000;

	APawn* ClosestFriend;
	APawn* FarthestFriend;
	bool IsIdle = false;
};
