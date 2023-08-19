// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBase.h"
#include "NetGameStateBase.h"
#include <GameFramework/PlayerState.h>
#include <UMG/Public/Components/TextBlock.h>

void UUIBase::NativeConstruct()
{
	Super::NativeConstruct();
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
