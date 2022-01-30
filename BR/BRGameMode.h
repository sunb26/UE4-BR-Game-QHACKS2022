// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BRGameMode.generated.h"

UCLASS(minimalapi)
class ABRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABRGameMode();

	// keeps track of who joins the game. Used to populat the array below
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Function for players being able to kill other players
	void PlayerDied(class ABRCharacter* Killed, class ABRCharacter* Killer);

	// Player state function for identifying a winner
	void WinnerFound(class ABRPlayerState* Winner);


	UPROPERTY(Transient) // Means don't save this to disk
	TArray<class ABRPlayerController*> AlivePlayers; //An array of all of the alive players. When you die, you are removed from this array until array is of size 1


};



