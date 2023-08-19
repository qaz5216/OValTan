// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API ANetGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	TArray<class APlayerState*> GetPlayerArrayByScore();
	UPROPERTY(Replicated)
	bool bGameStart=false;
};
