// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BRGameState.generated.h"

// Tells people about something - people can subscribe to it. We are using this to put the winner UI on screen
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinnerFound);


/**
 * 
 */
UCLASS()
class BR_API ABRGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	// Tells UE to replicate a value to everyone in the game
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	/**The winner of the match */
	// Replicated_using - everyone in game can know who the winner is
	// Transient - don't write to disk
	// Blueprint Read only - accessible by blueprints
	UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly, Category = "Game State")
	class ABRPlayerState* Winner = nullptr;

	UFUNCTION()
	void OnRep_Winner();

	/**Called when a winner is found */
	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FWinnerFound OnWinnerFound;
	
};
