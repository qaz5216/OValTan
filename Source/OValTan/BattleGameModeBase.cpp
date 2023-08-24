// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include <GameFramework/PlayerState.h>
#include "NetPlayerController.h"
#include <GameFramework/GameStateBase.h>
#include <GameFramework/PlayerStart.h>
#include "EngineUtils.h"
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

AActor* ABattleGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<APlayerStart*> playerStarts;
	playerStarts.SetNum(2);

	for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
	{
		APlayerStart* ps = *it;

		// 만일, 플레이어 스타트 액터의 태그가 "First"라면 홀수 번째 플레이어 스타트로 반환한다.
		// 그렇지 않다면, 짝수 번째 플레이어 스타트로 반환한다.
		if (ps->ActorHasTag(FName("First")))
		{
			playerStarts[0] = ps;
		}
		else
		{
			playerStarts[1] = ps;
		}
	}

	APlayerStart* chooseStart = playerStarts[callNumber];
	callNumber = (callNumber + 1) % playerStarts.Num();
	return chooseStart;
}
