// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NLHGunComponent.h"
#include "NLHGun.generated.h"

/**
 * A gun is made up of a tree of gun components, and can fire a variety of projectile types.
 */
UCLASS()
class NLH_API ANLHGun : public AActor
{
	GENERATED_BODY()
	

	/**
	 * The root component of the weapon.
	 */
	UPROPERTY()
	class ANLHGunComponent* GunComponent;

	/**
	 * Stores the amount of clips for this weapon that the player is currently carrying.
	 */
	UPROPERTY()
	int32 ClipCount;

public:
	/**
	 * The name of the gun.
	 */
	UPROPERTY()
	FString GunName;


	/**
	 * Gets the direction that the weapon should fire in, which includes any recoil or spread effects. 
	 */
	FRotator GetAimDirection();

	/**
	 * Causes the weapon to fire a projectile.
	 */
	void Fire();
	
	/**
	 * Reloads the weapon's clip.
	 */
	void Reload();

	/**
	 * Reduces the number of clips the players is carrying by one.
	 */
	void ReduceClips();

	/**
	 * Gets whether the player is currently carrying any reserve clips for this weapon or not.
	 *
	 * @return Returns true if there is at least one clip in reserve, false if there are none.
	 */
	bool HasClips();
};
