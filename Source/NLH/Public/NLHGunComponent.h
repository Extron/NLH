// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NLHProjectile.h"
#include "NLHDamageType.h"
#include "NLHGunComponent.generated.h"

class ANLHGun;

UENUM(BlueprintType)
enum class EGunComponentType : uint8
{
	GCTBase UMETA(DisplayName = "Base"),
	GCTBarrel UMETA(DisplayName = "Barrel"),
	GCTStock UMETA(DisplayName = "Stock"),
	GCTBarrelAttachment UMETA(DisplayName = "Barrel Attachment"),
	GCTMuzzleAttachment UMETA(DisplayName = "Muzzle Attachment"),
	GCTOptics UMETA(DisplayName = "Optics"),
	GCTClip UMETA(DisplayName = "Clip")
};

/**
 * A gun component is a single part of a gun, such as the base or barrel.  Each component has a set of children (specific components only allow certain children),
 * and maintains recursion logic for certain functionality, such as finding the bullet spawn point for the gun, or handling aim down sights.
 */
UCLASS(Abstract)
class NLH_API ANLHGunComponent : public AActor
{
	GENERATED_BODY()
	
	
	/**
	* A list of children components that this gun component has.
	*/
	UPROPERTY()
	TArray<ANLHGunComponent*> ChildComponents;

	/**
	* The parent gun component of this component.
	*/
	UPROPERTY()
	class ANLHGunComponent* ParentComponent;

public:
	/**
	* A list of gun components that are allowed as children to this component.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	TArray<FString> AllowedChildren;

	/**
	* A list of stats that this gun component contains.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	TArray<FString> Stats;

	/**
	* The mesh component used to draw this gun component.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	class USkeletalMeshComponent* MeshComponent;
	
	/**
	 * The category that the component belongs to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	EGunComponentType ComponentType;

	/**
	* The name of the gun component.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	FString Name;

	/**
	 * The description of the gun component.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	FString Description;

	/**
	* The name of the skeletal mesh socket that this component should be attached to.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Component")
	FName AttachSocket;



	/**
	 * Creates a new gun component and initializes the components for the object.
	 */
	ANLHGunComponent(const FObjectInitializer& ObjectInitializer);


	/**
	 * Recursively traverses the gun component tree to find the origin point for projectiles for the weapon.
	 *
	 * @param outVec - The world space location to use as the weapon's muzzle.
	 * @return Returns true if this component or a child was able to give a definite muzzle location.
	 */
	virtual bool FindMuzzlePoint(FVector& outVec)
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			if (child->FindMuzzlePoint(outVec))
				return true;
		}

		return false;
	}

	/**
	 * Recursively traverses the gun component tree to find the weapon's projectile class.
	 *
	 * @param outProjType - The projectile class to use for projectiles spawned by this weapon.
	 * @returns Returns true if this component or any of its children was able to give a definite projectile type.
	 */
	virtual bool FindProjectile(TSubclassOf<class ANLHProjectile>& outProjType)
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			if (child->FindProjectile(outProjType))
				return true;
		}

		return false;
	}

	/**
	* Recursively traverses the gun component tree to find the weapon's damage type.
	*
	* @param outDmgType - The damage type to use for damage done by this weapon.
	* @returns Returns true if this component or any of its children was able to give a definite damage type.
	*/
	virtual bool FindDamageType(TSubclassOf<class UNLHDamageType>& outDmgType)
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			if (child->FindDamageType(outDmgType))
				return true;
		}

		return false;
	}

	/**
	* Recursively traverses the gun component tree to find the weapon's clip capacity.
	*
	* @param outCapacity - The amount of ammo held by a single clip attached to this weapon.
	* @returns Returns true if this component or any of its children was able to give a definite clip capacity.
	*/
	virtual bool FindClipCapacity(int32& outCapacity)
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			if (child->FindClipCapacity(outCapacity))
				return true;
		}

		return false;
	}

	/**
	* Recursively traverses the gun component tree to find the amount of ammo currently in the weapon's clip.
	*
	* @param outCount - The amount of ammo currently held by the clip attached to this weapon.
	* @returns Returns true if this component or any of its children was able to give a definite clip count.
	*/
	virtual bool FindClipCount(int32& outCount)
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			if (child->FindClipCount(outCount))
				return true;
		}

		return false;
	}

	/**
	 * Recursively traverses the gun component tree to call the Fire method on every gun component.
	 * This will cause animations and sounds to play, projectiles to be fired, and particles to be spawned, 
	 * as per the specifics of each component.
	 */
	virtual void Fire()
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			child->Fire();
		}
	}

	/**
	* Recursively traverses the gun component tree to call the Reload method on every gun component.
	* This is the actual act of adding ammo into the weapon, and does not typically cause any animations to begin playing.
	*/
	virtual void Reload()
	{
		for (auto iter = GetChildIterator(); iter; iter++)
		{
			class ANLHGunComponent* child = *iter;

			child->Reload();
		}
	}

	/**
	 * Gets the root gun component of the weapon, usually the weapon base.
	 */
	ANLHGunComponent* GetRoot();

	/**
	 * Gets the constant array iterator for the child components of this gun component.
	 */
	TArray<ANLHGunComponent*>::TConstIterator GetChildIterator();

	/**
	* Adds a child component to this avatar component, if one can be added.  Returns whether the child component was added or not.
	*/
	bool AddChild(ANLHGunComponent* child);

	/**
	* Removes a child component from this avatar component, if the child exists.  Returns whether a child was removed or not.
	*/
	bool RemoveChild(ANLHGunComponent* child);

	/**
	* Determines whether this avatar component supports attaching a child with the specified name or not.
	*/
	bool CanAddChild(FString name);

	/**
	 * Sets the owner of all components in this gun component tree to be the container gun object.
	 */
	void SetGun(ANLHGun* gun);

	/**
	* Gets the gun container object that owns the gun component tree.
	*/
	ANLHGun* GetGun();

};
