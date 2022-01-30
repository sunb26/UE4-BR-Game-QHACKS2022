// Copyright Epic Games, Inc. All Rights Reserved.

#include "BRGameMode.h"
#include "BRHUD.h"
#include "BRCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include"BRPlayerController.h"
#include "BRPlayerState.h"
#include "BRGameState.h"

ABRGameMode::ABRGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABRHUD::StaticClass();
}

void ABRGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	AlivePlayers.Add(Cast<ABRPlayerController>(NewPlayer));
}

void ABRGameMode::PlayerDied(ABRCharacter* Killed, ABRCharacter* Killer)
{
	if (Killed) // Validates that player has been killed
	{
		if (ABRPlayerController* PC = Cast<ABRPlayerController>(Killed->GetController())) // Gets player controller who died
		{
			AlivePlayers.RemoveSingle(PC); // Removes player from array of alive players

		}

		// Checks if only one person is alive. If so, take the players state from the last array entry and pass it
		// through to the WinnerFound() function
		if (AlivePlayers.Num() == 1 && AlivePlayers.IsValidIndex(0))
		{
			WinnerFound(Cast<ABRPlayerState>(AlivePlayers[0]->PlayerState));
		}
	}
}

void ABRGameMode::WinnerFound(ABRPlayerState* Winner)
{
	if (ABRGameState* GS = GetGameState<ABRGameState>()) // Gets Game state
	{
		GS->Winner = Winner; //Sets the Gamestate Winner to the Player state that was passed to this function
	}
}
