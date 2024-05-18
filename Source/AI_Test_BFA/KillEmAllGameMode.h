// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy_Character.h"

#include "KillEmAllGameMode.generated.h"

/**
 *
 */
UCLASS()
class AI_TEST_BFA_API AKillEmAllGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void PawnKilled(APawn* PawnKilled);

protected:
	virtual void BeginPlay() override;

private:
	void EndGame(bool playerWon);
};
