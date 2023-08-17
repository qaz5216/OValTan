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

// ����� �Լ�
void ANetPlayerController::ServerRespawnPlayer_Implementation()
{
	if (gm != nullptr)
	{
		APawn* playerPawn = GetPawn();
		UnPossess();
		playerPawn->Destroy();

		// ó�� �������� PlayerStart ���� ��ġ���� ������
		//gm->RestartPlayer(this);

		// ������ Transform���� ������
		FTransform restartPoint;
		restartPoint.SetLocation(FVector(2200, 700, 300));
		gm->RestartPlayerAtTransform(this, restartPoint);
	}
}

void ANetPlayerController::ServerChangePlayerToSpectator_Implementation()
{
	// �÷��̾�κ��� Unpossess�� �Ѵ�.
	APawn* player = GetPawn();
	UnPossess();

	// ������ ���� �����Ѵ�.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ASpectatorPawn* spectator = GetWorld()->SpawnActor<ASpectatorPawn>(gm->SpectatorClass, player->GetTransform(), param);

		if (spectator != nullptr)
		{
			// ������ ������ ���� �����Ѵ�.
			Possess(spectator);
		}
	}

	// �÷��̾ �����Ѵ�.
	player->Destroy();

	// 5�� �ڿ� �������Ѵ�.
	FTimerHandle respawnHandle;

	GetWorldTimerManager().SetTimer(respawnHandle, this, &ANetPlayerController::ServerRespawnPlayer_Implementation, 5.0f, false);
}
