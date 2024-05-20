// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD)
		HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("PLAYER WON"));

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}