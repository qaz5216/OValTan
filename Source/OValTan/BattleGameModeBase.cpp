// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include <GameFramework/PlayerState.h>
#include "NetPlayerController.h"
#include <GameFramework/GameStateBase.h>

void ABattleGameModeBase::BeginPlay()
{	
	Super::BeginPlay();
	TArray<APlayerState*> players = GetWorld()->GetGameState()->PlayerArray;

	for (APlayerState* player : players)
	{
		if (player->GetPlayerController()->IsLocalController())
		{
			ANetPlayerController* Npc=Cast<ANetPlayerController>(player->GetPlayerController());
			Npc->bishost=true;
		}
	}
}
