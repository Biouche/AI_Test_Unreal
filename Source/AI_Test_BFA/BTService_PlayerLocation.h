// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class AI_TEST_BFA_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocation();
	
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float FlankingOffset = 500;
};
