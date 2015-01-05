// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "GCClip.h"

AGCClip::AGCClip(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Count = Capacity + 1;
}

bool AGCClip::FindProjectile(TSubclassOf<class ANLHProjectile>& outProjType)
{
	outProjType = ProjectileType;

	return true;
}

bool AGCClip::FindDamageType(TSubclassOf<class UNLHDamageType>& outDmgType)
{
	outDmgType = DamageType;
	return true;
}

void AGCClip::Fire()
{
	Super::Fire();

	if (Count > 0)
		Count--;
}

void AGCClip::Reload()
{
	Super::Reload();

	if (!GetGun()->HasClips())
		return;

	if (Count > 0)
		Count = Capacity + 1;
	else
		Count = Capacity;

	GetGun()->ReduceClips();
}