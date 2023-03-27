// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

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

	// update aim direction
	FVector loc, dir;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(loc, dir);

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, loc, loc + dir * 9999.f, ECollisionChannel::ECC_Visibility);

	aimDir = hit.Location - owner->GetActorLocation();
	aimDir.Normalize();
	aimDir.Z = 0.f;

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
	//DebugLogRed(1.f, TEXT("shooting"));

	lastShotTime = GetTime();

	AActor* shot = GetWorld()->SpawnActor<AActor>(projectile, owner->GetActorLocation(), owner->GetActorRotation());
	FVector speed = owner->GetVelocity();
	speed.Normalize();
	Cast<AProjectileBase>(shot)->Launch(aimDir, speed);
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