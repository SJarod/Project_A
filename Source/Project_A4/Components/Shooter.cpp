// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"

#include "../DebugHelpers.h"
#include "../Utils.h"

#include "Components/InputComponent.h"
#include "../Actors/ProjectileBase.h"

// Sets default values for this component's properties
UShooter::UShooter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	owner = GetOwner();
}

void UShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShooting && GetTimeSince(lastShotTime) >= shootingRate)
		Shoot();
}

void UShooter::StartShooting()
{
	bShooting = true;
}

void UShooter::StopShooting()
{
	bShooting = false;
}

void UShooter::Shoot()
{
	DebugLogRed(1.f, TEXT("shooting"));

	lastShotTime = GetTime();

	GetWorld()->SpawnActor<AActor>(projectile, owner->GetActorLocation(), owner->GetActorRotation());
}

// Called when the game starts
void UShooter::BeginPlay()
{
	Super::BeginPlay();

	// can shoot during game's first seconds
	lastShotTime = -shootingRate;


	// binding shoot action to input component of owner
	if (!owner || !owner->InputComponent)
		return;

	owner->InputComponent->BindAction("Shoot", IE_Pressed, this, &UShooter::StartShooting);
	owner->InputComponent->BindAction("Shoot", IE_Released, this, &UShooter::StopShooting);
}