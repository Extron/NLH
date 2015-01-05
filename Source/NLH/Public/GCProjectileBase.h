// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCBase.h"
#include "GCProjectileBase.generated.h"

/**
 * A projective gun base is one that emits projectiles that have a non-zero time of flight.
 */
UCLASS()
class NLH_API AGCProjectileBase : public AGCBase
{
	GENERATED_BODY()
	
	
public:
	virtual void Fire() override;

private:
	/**
	 * Spawns a particle that has a specified rotation, which will determine the direction of travel.
	 *
	 * @param rotation - The rotation of the projectile to spawn, which will determine the direction the projectile travels.
	 */
	void SpawnProjectile(FRotator rotation);
};
