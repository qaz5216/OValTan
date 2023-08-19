// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerController.h"
#include "BattleGameModeBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "OValTanCharacter.h"


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
		restartPoint.SetLocation(FVector(-1790, -2832, 191));
		if (respawnplayer!=nullptr)
		{
			respawnplayer->SetActorLocation(FVector(-1790, -2832, 191));
			Possess(respawnplayer);
		}
		else
		{
			gm->RestartPlayerAtTransform(this, restartPoint);
		}
	}
}

void ANetPlayerController::ServerChangePlayerToSpectator_Implementation()
{
	// �÷��̾�κ��� Unpossess�� �Ѵ�.
	respawnplayer = GetPawn();
	UnPossess();
	// ������ ���� �����Ѵ�.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ASpectatorPawn* spectator = GetWorld()->SpawnActor<ASpectatorPawn>(gm->SpectatorClass, respawnplayer->GetTransform(), param);

		if (spectator != nullptr)
		{
			// ������ ������ ���� �����Ѵ�.
			Possess(spectator);
		}
	}
	// 5�� �ڿ� �������Ѵ�.
	FTimerHandle respawnHandle;

	GetWorldTimerManager().SetTimer(respawnHandle, this, &ANetPlayerController::ServerRespawnPlayer_Implementation, 5.0f, false);
}

void ANetPlayerController::ServerChangePlayerToTracer_Implementation()
{
	APawn* player = GetPawn();
	UnPossess();

	// ������ ���� �����Ѵ�.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPTracer,player->GetTransform(), param);

		if (Charactor != nullptr)
		{
			// ������ ������ ���� �����Ѵ�.
			Possess(Charactor);
		}
	}

	// �÷��̾ �����Ѵ�.
	
	player->Destroy();
}

void ANetPlayerController::ServerChangePlayerToGenji_Implementation()
{
	APawn* player = GetPawn();
	UnPossess();
	UE_LOG(LogTemp, Warning, TEXT("Button-Warning-1"));
	// ������ ���� �����Ѵ�.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPGenji,player->GetTransform(), param);
		UE_LOG(LogTemp, Warning, TEXT("Button-Warning-2"));
		if (Charactor != nullptr)
		{

			UE_LOG(LogTemp, Warning, TEXT("Button-Warning-3"));
			// ������ ������ ���� �����Ѵ�.
			Possess(Charactor);
		}
	}

	// �÷��̾ �����Ѵ�.
	player->Destroy();

}
