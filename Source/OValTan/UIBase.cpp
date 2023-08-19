// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBase.h"
#include "NetGameStateBase.h"
#include <GameFramework/PlayerState.h>
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <UMG/Public/Components/Button.h>
#include "OValTanCharacter.h"

void UUIBase::NativeConstruct()
{
	Super::NativeConstruct();
	player = GetOwningPlayerPawn<AOValTanCharacter>();
	btn_Start->OnClicked.AddDynamic(this, &UUIBase::OnClickedStart);
	if (player->GetController()->HasAuthority())
	{
		SwitchCanvas(1);
	}
}

void UUIBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// 세션에 들어온 모든 플레이어의 정보 출력
	TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
	FString playersInfoText;

	for (APlayerState* p : players)
	{
		playersInfoText.Append(FString::Printf(TEXT("%s: %d\n"), *p->GetPlayerName(), (int32)p->GetScore()));
	}
	text_players->SetText(FText::FromString(playersInfoText));
}

void UUIBase::SwitchCanvas(int32 index)
{
	ws_SessionUISwitch->SetActiveWidgetIndex(index);
}

void UUIBase::OnClickedStart_Implementation()
{
	if(player->GetController()->HasAuthority())
	{
		TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
		for (APlayerState* p : players)
		{
			AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
			if (playerpawn!=nullptr)
			{
				p->SetScore(0);
				if (playerpawn->GetController()->IsLocalPlayerController())
				{
					playerpawn->Ingame_UI->SwitchCanvas(0);
				}
			}
		}
		GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = true;
	}
}
