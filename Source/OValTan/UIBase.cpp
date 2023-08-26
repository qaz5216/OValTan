// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBase.h"
#include "NetGameStateBase.h"
#include <GameFramework/PlayerState.h>
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <UMG/Public/Components/Button.h>
#include "OValTanCharacter.h"
#include "NetPlayerController.h"
#include "TabWidget.h"
#include <UMG/Public/Components/ScrollBox.h>
#include <UMG/Public/Components/Image.h>
#include "NetPlayerState.h"

void UUIBase::NativeConstruct()
{
	Super::NativeConstruct();
	player = GetOwningPlayerPawn<AOValTanCharacter>();
	btn_Start->OnClicked.AddDynamic(this, &UUIBase::OnClickedStart);
	
	MultiBuildStart();

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &UUIBase::PlayerSetting, 0.5, true, 0);
}

void UUIBase::PlayerSetting()
{
	// 세션에 들어온 모든 플레이어의 정보 출력
	TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
	//FString playersInfoText;
	sb_UserListBox->ClearChildren();
	int32 playernum = 1;
	for (APlayerState* p : players)
	{
		UTabWidget* myTabSlot;
		ANetPlayerState*Nps=Cast<ANetPlayerState>(p);
		if (Nps!=nullptr)
		{
			if (Nps->charnum== 1)
			{
				myTabSlot = CreateWidget<UTabWidget>(GetWorld(), Tabsession);
			}
			else
			{
				myTabSlot = CreateWidget<UTabWidget>(GetWorld(), Tabsession_t);
			}
		if (myTabSlot != nullptr)
		{
			if (playernum%2==1)
			{
				myTabSlot->img_back->SetColorAndOpacity(FLinearColor(0,0,0.5,0.7));
			}
			myTabSlot->text_Num->SetText(FText::FromString(FString::Printf(TEXT("%d"), playernum++)));
			myTabSlot->text_UserName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *p->GetPlayerName())));
			myTabSlot->text_KillCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int32)p->GetScore())));
			sb_UserListBox->AddChild(myTabSlot);
		}
		//playersInfoText.Append(FString::Printf(TEXT("%s: %d\n"), *p->GetPlayerName(), (int32)p->GetScore()));
		}
	}
	//text_players->SetText(FText::FromString(playersInfoText));
	
}


void UUIBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bCountStart)
	{
		if (CountCur > 0)
		{
			CountCur -= InDeltaTime;
			if (text_count != nullptr)
			{
				text_count->SetText(FText::AsNumber((int32)(CountCur + 1)));
			}
		}
		else
		{
			bCountStart = false;
			CountCur = CountMax;
			text_count->SetVisibility(ESlateVisibility::Hidden);
			SwitchCanvas(0);
		}
	}


}

void UUIBase::SwitchCanvas(int32 index)
{
	Canvasindex = index;
	ws_SessionUISwitch->SetActiveWidgetIndex(index);

}

void UUIBase::OnClickedStart_Implementation()
{
	if (player->GetController()->HasAuthority())
	{
		TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
		for (APlayerState* p : players)
		{
			AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
			if (playerpawn != nullptr)
			{
				p->SetScore(0);
				if (playerpawn->GetController()->IsLocalPlayerController())
				{
					playerpawn->Ingame_UI->SwitchCanvas(3);
					CountDown();
				}
				else
				{
					ANetPlayerController* Npc = playerpawn->GetController<ANetPlayerController>();
					Npc->ChangeUIGameStart(3);
				}
			}
		}
		GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = true;
		//MultiOnClickedStart();
	}
}

void UUIBase::MultiOnClickedStart_Implementation()
{
	GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = true;
}

void UUIBase::MultiBuildStart_Implementation()
{
	if (!GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart)
	{
		TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
		for (APlayerState* p : players)
		{
			AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
			UE_LOG(LogTemp, Warning, TEXT("playerpawn = %s"), playerpawn != nullptr ? *FString("YesPawn") : *FString("NuLL"));
			if (playerpawn != nullptr)
			{
				if (playerpawn->GetController() != nullptr)
				{
					ANetPlayerController* Npc = playerpawn->GetController<ANetPlayerController>();
					if (Npc->bishost)
					{
						SwitchCanvas(1);
					}
					else
					{
						SwitchCanvas(2);
					}
				}
			}
		}
	}

}

void UUIBase::CountDown()
{
	CountCur = CountMax;
	text_count->SetVisibility(ESlateVisibility::Visible);
	bCountStart = true;
}
