// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NLHAvatarComponent.h"
#include "NLHAvatar.generated.h"

/**
 * An avatar is used to draw the physical representation of a player's character.  Avatars are made up of a tree of 
 * avatar components, each component containing a unique set of properties and functions.  Examples of such components
 * are body parts, armor, and clothes.
 */
UCLASS()
class NLH_API ANLHAvatar : public AActor
{
	GENERATED_BODY()
	
	/**
	 * The root avatar component of the avatar.
	 */
	UPROPERTY()
	class ANLHAvatarComponent* AvatarComponent;
	
};
