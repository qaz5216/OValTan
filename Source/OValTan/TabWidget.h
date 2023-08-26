// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TabWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API UTabWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_Num;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_UserName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_KillCount;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* img_back;


};
