// Fill out your copyright notice in the Description page of Project Settings.


#include "BRGameState.h"
#include "Net/UnrealNetwork.h"

void ABRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicates the winner
	DOREPLIFETIME(ABRGameState, Winner);
}

void ABRGameState::OnRep_Winner()
{
	OnWinnerFound.Broadcast();
}
