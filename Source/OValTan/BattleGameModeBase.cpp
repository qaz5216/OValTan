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

		// ����, �÷��̾� ��ŸƮ ������ �±װ� "First"��� Ȧ�� ��° �÷��̾� ��ŸƮ�� ��ȯ�Ѵ�.
		// �׷��� �ʴٸ�, ¦�� ��° �÷��̾� ��ŸƮ�� ��ȯ�Ѵ�.
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
