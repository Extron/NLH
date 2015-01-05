// Fill out your copyright notice in the Description page of Project Settings.

#include "NLH.h"
#include "NLHAvatarComponent.h"

bool ANLHAvatarComponent::AddChild(ANLHAvatarComponent* child)
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

bool ANLHAvatarComponent::RemoveChild(ANLHAvatarComponent* child)
{
	if (ChildComponents.Remove(child) > 0)
	{
		child->DetachRootComponentFromParent();
		child->ParentComponent = NULL;

		return true;
	}

	return false;
}

bool ANLHAvatarComponent::CanAddChild(FString name)
{
	return AllowedChildren.Contains(name);
}



