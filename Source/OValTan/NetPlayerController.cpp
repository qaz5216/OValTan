// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerController.h"
#include "BattleGameModeBase.h"
#include "GameFramework/SpectatorPawn.h"


void ANetPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		gm = GetWorld()->GetAuthGameMode<ABattleGameModeBase>();
	}
}

// 재시작 함수
void ANetPlayerController::ServerRespawnPlayer_Implementation()
{
	if (gm != nullptr)
	{
		APawn* playerPawn = GetPawn();
		UnPossess();
		playerPawn->Destroy();

		// 처음 배정받은 PlayerStart 액터 위치에서 리스폰
		//gm->RestartPlayer(this);

		// 지정된 Transform에서 리스폰
		FTransform restartPoint;
		restartPoint.SetLocation(FVector(2200, 700, 300));
		gm->RestartPlayerAtTransform(this, restartPoint);
	}
}

void ANetPlayerController::ServerChangePlayerToSpectator_Implementation()
{
	// 플레이어로부터 Unpossess를 한다.
	APawn* player = GetPawn();
	UnPossess();

	// 관전자 폰을 생성한다.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ASpectatorPawn* spectator = GetWorld()->SpawnActor<ASpectatorPawn>(gm->SpectatorClass, player->GetTransform(), param);

		if (spectator != nullptr)
		{
			// 생성된 관전자 폰에 빙의한다.
			Possess(spectator);
		}
	}

	// 플레이어를 제거한다.
	player->Destroy();

	// 5초 뒤에 리스폰한다.
	FTimerHandle respawnHandle;

	GetWorldTimerManager().SetTimer(respawnHandle, this, &ANetPlayerController::ServerRespawnPlayer_Implementation, 5.0f, false);
}
