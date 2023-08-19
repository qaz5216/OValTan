// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameStateBase.h"
#include "GameFramework/PlayerState.h"


TArray<APlayerState*> ANetGameStateBase::GetPlayerArrayByScore()
{
	TArray<APlayerState*> sortedPlayers = PlayerArray;

	sortedPlayers.Sort([](const APlayerState& p1, const APlayerState& p2) { return p1.GetScore() > p2.GetScore(); });
	return sortedPlayers;
}

void ANetGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}