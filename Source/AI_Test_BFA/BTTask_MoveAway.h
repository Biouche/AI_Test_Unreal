// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveAway.generated.h"

/**
 * 
 */
UCLASS()
class AI_TEST_BFA_API UBTTask_MoveAway : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveAway();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
