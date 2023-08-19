// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerState.h"
#include "NetGameInstance.h"
#include "NetGameStateBase.h"
#include "OValTanCharacter.h"
#include "UIBase.h"


void ANetPlayerState::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UNetGameInstance>(GetGameInstance());

	if (gi != nullptr && GetPlayerController() != nullptr && GetPlayerController()->IsLocalPlayerController())
	{
		SetMyName(gi->mySessionName);
	}
}

void ANetPlayerState::SetMyName_Implementation(const FString& myName)
{
	SetPlayerName(myName);
}

void ANetPlayerState::SetKillScore_Implementation(float NewScore)
{
	SetScore(NewScore);
	if (NewScore > 5)
	{
		ANetGameStateBase* GS = GetWorld()->GetGameState<ANetGameStateBase>();
		if (GS != nullptr)
		{
			GS->bGameStart = false;
			if (HasAuthority())
			{
				AOValTanCharacter* player=GetPawn<AOValTanCharacter>();
				player->Ingame_UI->SwitchCanvas(1);
			}
		}
	}
}

