// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UProgressBar* pb_healthBar;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	class AEnemyDummy* Enemy;
};
