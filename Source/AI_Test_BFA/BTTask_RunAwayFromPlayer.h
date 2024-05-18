// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunAwayFromPlayer.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class AI_TEST_BFA_API UBTTask_RunAwayFromPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RunAwayFromPlayer();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float MoveAwayDistance = 50;
	
};
