// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateClosestFriendLocation.generated.h"

/**
 * 
 */
UCLASS()
class AI_TEST_BFA_API UBTS_UpdateClosestFriendLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_UpdateClosestFriendLocation();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
