// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLHGunComponent.h"
#include "GCBarrel.generated.h"

/**
 * 
 */
UCLASS()
class NLH_API AGCBarrel : public ANLHGunComponent
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite)
	FName MuzzleSocket;


	/**
	 * Barrel components must be able to return a muzzle component to serve as the source of projectiles spawned from this weapon.
	 */
	virtual bool FindMuzzlePoint(FVector& outVec) override;
};
