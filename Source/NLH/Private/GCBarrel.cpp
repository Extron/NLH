// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "GCBarrel.h"

bool AGCBarrel::FindMuzzlePoint(FVector& outVec)
{
	outVec = MeshComponent->GetSocketLocation(MuzzleSocket);

	return true;
}


