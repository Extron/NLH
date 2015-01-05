// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLHGunComponent.h"
#include "GCClip.generated.h"

/**
 * Clips are gun components that dictate the type of projectiles that are fired from a weapon and how many the weapon holds.
 */
UCLASS(Abstract)
class NLH_API AGCClip : public ANLHGunComponent
{
	GENERATED_BODY()

	/**
	 * The current amount of projectiles that are in the clip.
	 */
	UPROPERTY()
	int32 Count;

public:
	/**
	 * The amount of projectiles that the clip can hold.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 Capacity;
	
	/**
	 * The type of projectile that this clip contains.
	 */
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class ANLHProjectile> ProjectileType;

	/**
	 * The damage type that the projectiles in this clip do when they hit something.
	 */
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UNLHDamageType> DamageType;


	/**
	 * Creates a new clip and initializes its properties.
	 */
	AGCClip(const FObjectInitializer& ObjectInitializer);

	/**
	 * A clip will always be able to return a definite projectile type.
	 * 
	 * @param outProjType - The projectile type that this clip stores.
	 * @return Clips always return true, since they have a definite projectile type.
	 */
	virtual bool FindProjectile(TSubclassOf<class ANLHProjectile>& outProjType) override;

	/**
	* A clip will always be able to return a definite damage type.
	*
	* @param outDmgType - The damage type that this clip stores.
	* @return Clips always return true, since they have a definite damage type.
	*/
	virtual bool FindDamageType(TSubclassOf<class UNLHDamageType>& outDmgType) override;

	/**
	 * Removes a single projectile from the clip.
	 */
	virtual void Fire() override;

	/**
	 * Refills the clip with fresh ammo, and decreases the amount of clips being carried by the player.
	 */
	virtual void Reload() override;
};
