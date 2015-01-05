// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "NLH.h"
#include "NLHGameMode.h"
#include "NLHHUD.h"
#include "NLHCharacter.h"

ANLHGameMode::ANLHGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANLHHUD::StaticClass();
}
