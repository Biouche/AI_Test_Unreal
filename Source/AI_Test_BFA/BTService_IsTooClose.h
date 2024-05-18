// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsTooClose.generated.h"

/**
 * 
 */
UCLASS()
class AI_TEST_BFA_API UBTService_IsTooClose : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_IsTooClose();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
