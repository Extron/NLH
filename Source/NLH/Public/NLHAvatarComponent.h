// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Array.h"

#include "NLHAvatarComponent.generated.h"

/**
 * An avatar component is a single node in any given avatar tree.  It may have a parent or children components.  
 * Avatar components contain skeletal meshes used to draw themselves.
 */
UCLASS(Blueprintable)
class NLH_API ANLHAvatarComponent : public AActor
{
	GENERATED_BODY()


	/**
	 * A list of children components that this avatar component has.
	 */
	UPROPERTY()
	TArray<ANLHAvatarComponent*> ChildComponents;

	/**
	 * The parent avatar component of this component.
	 */
	UPROPERTY()
	class ANLHAvatarComponent* ParentComponent;


public:
	/**
	 * A list of avatar components that are allowed as children to this component.
	 */
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> AllowedChildren;

	/**
	 * A list of stats that this component contains.
	 */
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Stats;

	/**
	* The mesh component used to draw the avatar component.
	*/
	UPROPERTY(BlueprintReadWrite, Category = Display)
	class USkeletalMeshComponent* MeshComponent;

	/**
	* The name of the avatar component.
	*/
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	/**
	* The name of the skeletal mesh socket that this component should be attached to.
	*/
	UPROPERTY(BlueprintReadWrite)
	FName AttachSocket;


	/**
	 * Adds a child component to this avatar component, if one can be added.  Returns whether the child component was added or not.
	 */
	bool AddChild(ANLHAvatarComponent* child);

	/**
	 * Removes a child component from this avatar component, if the child exists.  Returns whether a child was removed or not.
	 */
	bool RemoveChild(ANLHAvatarComponent* child);

	/**
	 * Determines whether this avatar component supports attaching a child with the specified name or not.
	 */
	bool CanAddChild(FString name);
};
