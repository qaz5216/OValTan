// Copyright Epic Games, Inc. All Rights Reserved.

#include "OValTanGameMode.h"
#include "OValTanCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOValTanGameMode::AOValTanGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));*/
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/JJH/blueprint/BP_Genji2"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
