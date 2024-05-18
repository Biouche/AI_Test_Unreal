// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsLonely.generated.h"

/**
 * 
 */
UCLASS()
class AI_TEST_BFA_API UBTService_IsLonely : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_IsLonely();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
