// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetPlayerController.generated.h"


/**
 */
UCLASS()
class OVALTAN_API ANetPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	class ABattleGameModeBase* gm;
	
	class APawn* respawnplayer;
	UFUNCTION(Server, Unreliable)
	void ServerRespawnPlayer();

	UFUNCTION(Server, Unreliable)
	void ServerChangePlayerToSpectator();

	UFUNCTION(Server, Unreliable)
	void ServerChangePlayerToTracer();

	UFUNCTION(Server, Unreliable)
	void ServerChangePlayerToGenji();
	
	UFUNCTION(NetMulticast,Reliable)
	void MutiRespawnPlayer(class ASpectatorPawn* spc);


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Character)
	TSubclassOf<class AOValTanCharacter> BPTracer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Character)
	TSubclassOf<class AOValTanCharacter> BPGenji;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Character)
	TSubclassOf<class ASpectatorPawn> Spec;

};
