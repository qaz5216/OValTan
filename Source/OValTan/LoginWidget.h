// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API ULoginWidget : public UUserWidget
{
		GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;


public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UEditableText* edit_roomName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class USlider* slider_playerCount;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_sliderCount;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_CreateSession;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UScrollBox* sb_RoomListBox;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_FindSession;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_SessionUISwitch;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_CreateSelection;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_FindSelection;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_BackFromCreate;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_BackFromFind;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UEditableText* edit_userName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Next;

	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class USessionInfoWidget> sessionInfoWidget;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* StartAnim;

	UFUNCTION()
	void OnClickCreateButton();

	UFUNCTION()
	void OnSliderMoved(float value);

	UFUNCTION()
	void OnClickedCreateSelection();

	UFUNCTION()
	void OnClickedFindSelection();

	UFUNCTION()
	void OnClickFindButton();

	UFUNCTION()
	void OnClickNextButton();

	UFUNCTION()
	void AddRoomSlot(struct FSessionSlotInfo slotInfo);

	UFUNCTION()
	void ChangeButtonActivation(bool bIsActivation);

private:
	UPROPERTY()
	class UNetGameInstance* gi;

	UPROPERTY()
	class USessionInfoWidget* sessionSlot;
	
	UFUNCTION()
	void BackToFirstCanvas();

	void SwitchCanvas(int32 index);

	UFUNCTION()
	void PlayStartAnim();
};
