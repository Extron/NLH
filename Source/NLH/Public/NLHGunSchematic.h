// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "NLHGunComponent.h"
#include "NLHGunSchematic.generated.h"

USTRUCT()
struct FComponentSchematic
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TSubclassOf<ANLHGunComponent> ComponentClass;

	UPROPERTY()
	TArray<int32> Children;
};

/**
 * This class stores the schematic for a gun, and is used to build the actual weapon during gameplay.
 */
UCLASS()
class NLH_API UNLHGunSchematic : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * A list of all gun component schematics used to build the gun, flattened in a depth-first manner.  The root component
	 * is always assumed to be the first element of this list.
	 */
	UPROPERTY()
		TArray<FComponentSchematic> ComponentSchematics;
	
	
	/**
	 * Creates a new gun component tree from this schematic.
	 */
	class ANLHGunComponent* CreateGun();

	/**
	 * Converts the specified gun component tree into a schematic.
	 */
	void DisassembleGun(class ANLHGunComponent* gun);

private:
	class ANLHGunComponent* CreateComponent(FComponentSchematic schematic);

	int32 DisassembleComponent(class ANLHGunComponent* component);
};
