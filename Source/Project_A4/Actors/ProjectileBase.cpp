// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"

#include "../Utils.h"
#include "../DebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateComponent(USphereComponent);
	ProjectileMovement = CreateComponent(UProjectileMovementComponent);
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	birthTime = GetTime();

	// firing
	ProjectileMovement->SetActive(true);
	ProjectileMovement->Velocity = dir * ProjectileMovement->InitialSpeed;
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetTimeSince(birthTime) > lifeTime)
		Destroy();
}