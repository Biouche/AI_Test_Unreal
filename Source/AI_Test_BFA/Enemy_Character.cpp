// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Character.h"
#include "KillEmAllGameMode.h"
#include "Components\CapsuleComponent.h"
#include "Kismet\GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy_Character::AEnemy_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

// Called every frame
void AEnemy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
		return;

	//UCharacterMovementComponent* Movement = GetCharacterMovement();
	float DistanceToPlayer = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Distance to player : %f"), DistanceToPlayer);

	if (FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()) > 2000)
	{
		GetCharacterMovement()->MaxWalkSpeed = 150;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 300;
	}

}

// Called to bind functionality to input
void AEnemy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemy_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Enemy Health left %f"), Health);

	if (IsDead())
	{
		AKillEmAllGameMode* GameMode = GetWorld()->GetAuthGameMode<AKillEmAllGameMode>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AEnemy_Character::IsDead() const
{
	return Health <= 0;
}
