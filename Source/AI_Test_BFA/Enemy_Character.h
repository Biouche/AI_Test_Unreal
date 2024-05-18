// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_Character.generated.h"

UCLASS()
class AI_TEST_BFA_API AEnemy_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:

	UPROPERTY(EditAnywhere)
	float RotationRate = 1;

	UPROPERTY(EditAnywhere)
	float CautiousWalkSpeed = 150;

	UPROPERTY(EditAnywhere)
	float FastWalkSpeed = 300;

	UPROPERTY(EditAnywhere)
	float FastWalkSpeedDistance = 2000;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
