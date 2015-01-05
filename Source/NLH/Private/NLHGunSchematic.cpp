// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "NLHGunSchematic.h"


ANLHGunComponent* UNLHGunSchematic::CreateGun()
{
	return CreateComponent(ComponentSchematics[0]);
}

void UNLHGunSchematic::DisassembleGun(class ANLHGunComponent* gun)
{
	DisassembleComponent(gun);
}

ANLHGunComponent* UNLHGunSchematic::CreateComponent(FComponentSchematic schematic)
{
	UWorld* world = GetWorld();

	if (!world)
		return NULL;

	class ANLHGunComponent* component = world->SpawnActor<class ANLHGunComponent>(schematic.ComponentClass);

	for (int i = 0; i < schematic.Children.Num(); i++)
		component->AddChild(CreateComponent(ComponentSchematics[schematic.Children[i]]));

	return component;
}

int32 UNLHGunSchematic::DisassembleComponent(class ANLHGunComponent* component)
{
	FComponentSchematic schematic = FComponentSchematic();

	schematic.ComponentClass = component->StaticClass();

	ComponentSchematics.Push(schematic);

	int32 index = ComponentSchematics.Num() - 1;

	for (auto iter = component->GetChildIterator(); iter; iter++)
	{
		class ANLHGunComponent* child = *iter;

		ComponentSchematics[index].Children.Push(DisassembleComponent(child));
	}

	return index;
}




