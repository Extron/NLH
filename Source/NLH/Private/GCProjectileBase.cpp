// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "GCProjectileBase.h"

void AGCProjectileBase::Fire()
{
	SpawnProjectile(Cast<ANLHGun>(GetOwner())->GetAimDirection());
}

void AGCProjectileBase::SpawnProjectile(FRotator rotation)
{
	UWorld* const world = GetWorld();

	if (!world)
		return;

	FVector muzzleLoc = FVector();
	TSubclassOf<ANLHProjectile> projType = ANLHProjectile::StaticClass();

	if (FindProjectile(projType) && FindMuzzlePoint(muzzleLoc))
		world->SpawnActor<ANLHProjectile>(projType, muzzleLoc, rotation);
}


