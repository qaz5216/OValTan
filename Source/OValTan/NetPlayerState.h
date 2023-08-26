// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void SetMyName(const FString& myName);
	UFUNCTION(Server, Reliable)
	void SetKillScore(float NewScore);
	UFUNCTION(NetMulticast, Reliable)
	void SetEndUI();

	UPROPERTY()
	int32 charnum=1;
private:
	class UNetGameInstance* gi;
		
};
