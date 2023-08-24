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
	UFUNCTION()
	void CountDown();
	UPROPERTY()
	bool bCountStart=false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = MySettings)
	int32 UI_HP_Cur;
};
