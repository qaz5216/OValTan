// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBase.h"
#include "NetGameStateBase.h"
#include <GameFramework/PlayerState.h>
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <UMG/Public/Components/Button.h>
#include "OValTanCharacter.h"
#include "NetPlayerController.h"

void UUIBase::NativeConstruct()
{
	Super::NativeConstruct();
	player = GetOwningPlayerPawn<AOValTanCharacter>();
	btn_Start->OnClicked.AddDynamic(this, &UUIBase::OnClickedStart);
	TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
	for (APlayerState* p : players)
	{
		AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
		UE_LOG(LogTemp, Warning, TEXT("playerpawn = %s"),playerpawn!=nullptr ? *FString("YesPawn") :*FString("NuLL"));
		if (playerpawn != nullptr)
		{
			p->SetScore(0);
			if (playerpawn->GetController()!=nullptr)
			{
				if (playerpawn->GetController()->IsLocalPlayerController())
				{
					playerpawn->Ingame_UI->SwitchCanvas(1);
				}
			}
		}
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
	if (bCountStart)
	{
		if (CountCur>0)
		{
			CountCur -= InDeltaTime;
			text_count->SetText(FText::AsNumber((int32)(CountCur + 1)));
		}
		else
		{
			bCountStart = false;
			CountCur = CountMax;
			text_count->SetVisibility(ESlateVisibility::Hidden);
			SwitchCanvas(2);
		}
	}
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
					playerpawn->Ingame_UI->SwitchCanvas(3);
					CountDown();
				}
				else
				{
					ANetPlayerController* Npc=playerpawn->GetController<ANetPlayerController>();
					Npc->ChangeUIGameStart(3);
				}
			}
		}
		GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = true;
	}
}

void UUIBase::CountDown()
{
	CountCur = CountMax;
	text_count->SetVisibility(ESlateVisibility::Visible);
	bCountStart = true;
}
