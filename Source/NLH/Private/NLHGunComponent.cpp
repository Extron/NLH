// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "NLHGun.h"
#include "NLHGunComponent.h"


ANLHGunComponent::ANLHGunComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MeshComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, "MeshComponent");
	RootComponent = MeshComponent;
}

ANLHGunComponent* ANLHGunComponent::GetRoot()
{
	if (!ParentComponent)
		return ParentComponent->GetRoot();
	else
		return this;
}

TArray<ANLHGunComponent*>::TConstIterator ANLHGunComponent::GetChildIterator()
{
	return ChildComponents.CreateConstIterator();
}


bool ANLHGunComponent::AddChild(ANLHGunComponent* child)
{
	if (CanAddChild(child->Name))
	{
		ChildComponents.Add(child);

		child->AttachRootComponentTo(MeshComponent, child->AttachSocket);
		child->ParentComponent = this;

		return true;
	}

	return false;
}

bool ANLHGunComponent::RemoveChild(ANLHGunComponent* child)
{
	if (ChildComponents.Remove(child) > 0)
	{
		child->DetachRootComponentFromParent();
		child->ParentComponent = NULL;

		return true;
	}

	return false;
}

bool ANLHGunComponent::CanAddChild(FString name)
{
	return AllowedChildren.Contains(name);
}

void ANLHGunComponent::SetGun(ANLHGun* gun)
{
	SetOwner(gun);

	for (auto iter = GetChildIterator(); iter; iter++)
	{
		class ANLHGunComponent* child = *iter;

		child->SetGun(gun);
	}
}

ANLHGun* ANLHGunComponent::GetGun()
{
	return Cast<ANLHGun>(GetOwner());
}
