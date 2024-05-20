// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet\GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::Shoot()
{
	// Spawn shooting effect
	UGameplayStatics::SpawnEmitterAttached(ShootingEffect, Mesh, TEXT("EffectSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	// Prepare shoot from viewport
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector ViewportLocation;
	FRotator ViewportRotation;

	OwnerController->GetPlayerViewPoint(ViewportLocation, ViewportRotation);

	FVector End = ViewportLocation + ViewportRotation.Vector() * MaxRange;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	bool hasHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewportLocation, End, ECC_GameTraceChannel1, CollisionParams);

	if (hasHit) // Shooting successful
	{
		FVector ShotDirection = -ViewportRotation.Vector();
		// Spawn impact
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());

		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}
