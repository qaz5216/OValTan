// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UScaleBox* ScaleBox1;
	class USizeBox* SizeBox1;
	class UCanvasPanel* Canvas1;
	class UCanvasPanel* Canvas2;
	class UCanvasPanel* Canvas3;
	class UCanvasPanel* Canvas4;
	class UCanvasPanel* Canvas5;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_players;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_count;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	float CountMax=5;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	float CountCur=CountMax;
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UTabWidget> Tabsession;
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UTabWidget> Tabsession_t;
	UPROPERTY()
	class UTabWidget* TabSlot;

	UFUNCTION()
	void PlayerSetting();

	UPROPERTY(VisibleAnywhere,Category = MySettings)
	int32 faceindex=1;



	UPROPERTY(VisibleAnywhere,Category = MySettings)
	int32 Canvasindex;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UScrollBox* sb_UserListBox;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Start;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_SessionUISwitch;
	void SwitchCanvas(int32 index);
	class AOValTanCharacter* player;
	UFUNCTION(Server,Reliable)
	void OnClickedStart();
	UFUNCTION(NetMulticast,Reliable)
	void MultiOnClickedStart();

	UFUNCTION(NetMulticast,Reliable)
	void MultiBuildStart();

	UFUNCTION()
	void CountDown();
	UFUNCTION()
	void CountStart();
	UPROPERTY()
	bool bCountStart=false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = MySettings)
	int32 UI_HP_Cur;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	USoundBase* GameStartVoice;


	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* GameReady;
	UFUNCTION()
	void PlayGameReady();

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* Dead;
	UFUNCTION()
	void PlayDead();

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* Hitted;
	UFUNCTION()
	void PlayHitted();

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* Healing;
	UFUNCTION()
	void PlayHealing();



};
