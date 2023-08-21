// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "NetGameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "SessionInfoWidget.h"
#include "Components/ScrollBox.h"

void ULoginWidget::NativeConstruct()
{
	gi = GetGameInstance<UNetGameInstance>();

	btn_CreateSession->OnClicked.AddDynamic(this, &ULoginWidget::OnClickCreateButton);
	slider_playerCount->OnValueChanged.AddDynamic(this, &ULoginWidget::OnSliderMoved);
	btn_CreateSelection->OnClicked.AddDynamic(this, &ULoginWidget::OnClickedCreateSelection);
	btn_FindSelection->OnClicked.AddDynamic(this, &ULoginWidget::OnClickedFindSelection);
	btn_FindSession->OnClicked.AddDynamic(this, &ULoginWidget::OnClickFindButton);
	btn_BackFromCreate->OnClicked.AddDynamic(this, &ULoginWidget::BackToFirstCanvas);
	btn_BackFromFind->OnClicked.AddDynamic(this, &ULoginWidget::BackToFirstCanvas);
	btn_Next->OnClicked.AddDynamic(this, &ULoginWidget::OnClickNextButton);
	text_sliderCount->SetText(FText::AsNumber((int32)2));
	if (gi != nullptr)
	{
		gi->onSearchCompleted.AddDynamic(this, &ULoginWidget::AddRoomSlot);
		gi->onFindButtonActivation.AddDynamic(this, &ULoginWidget::ChangeButtonActivation);
	}
	PlayStartAnim();
}

void ULoginWidget::OnClickCreateButton()
{
	UE_LOG(LogTemp, Warning, TEXT("COCOCOCO"));
	if (gi != nullptr && !edit_roomName->GetText().IsEmpty())
	{
		gi->CreateMySession(edit_roomName->GetText(), (int32)slider_playerCount->GetValue());
	}
}

void ULoginWidget::OnSliderMoved(float value)
{
	text_sliderCount->SetText(FText::AsNumber((int32)value));
}

void ULoginWidget::OnClickedCreateSelection()
{
	SwitchCanvas(2);
}

void ULoginWidget::OnClickedFindSelection()
{
	SwitchCanvas(3);
	OnClickFindButton();
}

void ULoginWidget::OnClickFindButton()
{
	if (gi != nullptr)
	{
		gi->FindOtherSession();
		sb_RoomListBox->ClearChildren();
	}
}

void ULoginWidget::OnClickNextButton()
{
	if (!edit_userName->GetText().IsEmpty())
	{
		gi->mySessionName = edit_userName->GetText().ToString();
		SwitchCanvas(1);
	}
}

void ULoginWidget::AddRoomSlot(FSessionSlotInfo slotInfo)
{
	// ���� ������ �����Ѵ�.
	sessionSlot = CreateWidget<USessionInfoWidget>(GetWorld(), sessionInfoWidget);

	if (sessionSlot != nullptr)
	{
		// ���� ������ �� ��ҿ� ���� ������ �ִ´�.
		sessionSlot->text_RoomName->SetText(FText::FromString(slotInfo.roomName));
		sessionSlot->text_HostName->SetText(FText::FromString(slotInfo.hostName));
		sessionSlot->text_PlayerCount->SetText(FText::FromString(slotInfo.playerCount));
		sessionSlot->text_PingSpeed->SetText(FText::AsNumber(slotInfo.pingSpeed));
		sessionSlot->sessionIndex = slotInfo.sessionIndex;

		// ������ ���� ������ ��ũ�� �ڽ��� �ڽ����� �߰��Ѵ�.
		sb_RoomListBox->AddChild(sessionSlot);
	}
}

void ULoginWidget::ChangeButtonActivation(bool bIsActivation)
{
	btn_FindSession->SetIsEnabled(bIsActivation);
}

void ULoginWidget::BackToFirstCanvas()
{
	ws_SessionUISwitch->SetActiveWidgetIndex(1);
}

void ULoginWidget::SwitchCanvas(int32 index)
{
	ws_SessionUISwitch->SetActiveWidgetIndex(index);
}

void ULoginWidget::PlayStartAnim()
{
	PlayAnimationForward(StartAnim);
}


