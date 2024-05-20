// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework\Controller.h"
#include "Kismet\GameplayStatics.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	AZombie_AIController* EnemyCharacter = Cast<AZombie_AIController>(PawnKilled->GetController());
	if (EnemyCharacter)
	{
		// Remove enemy from array 
		Enemies.Remove(EnemyCharacter);
		if (Enemies.Num() == 0)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
				PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
		}
	}
}
