// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework\Controller.h"
#include "Kismet\GameplayStatics.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController) // Game Over
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AKillEmAllGameMode::EndGame(bool playerWon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool isWinner = Controller->IsPlayerController() == playerWon;
		Controller->GameHasEnded(Controller->GetPawn(), isWinner);
	}
}
