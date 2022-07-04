// Copyright Epic Games, Inc. All Rights Reserved.

#include "DogkieGameMode.h"
#include "DogkieCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADogkieGameMode::ADogkieGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
