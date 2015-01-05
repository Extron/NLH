// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "NLHGun.h"


void ANLHGun::Fire()
{
	if (GunComponent)
		GunComponent->Fire();
}

void ANLHGun::Reload()
{
}

void ANLHGun::ReduceClips()
{
	if (ClipCount > 0)
		ClipCount--;
}

bool ANLHGun::HasClips()
{
	return ClipCount > 0;
}

