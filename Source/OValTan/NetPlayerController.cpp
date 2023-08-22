// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerController.h"
#include "BattleGameModeBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "OValTanCharacter.h"
#include "UIBase.h"


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
	if (respawnplayer==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("respawnPlayer is %s"), respawnplayer != nullptr ? *respawnplayer->GetName() : *FString("NuLL"));
		return;
	}
	APawn* playerPawn = GetPawn();
	UnPossess();
	playerPawn->Destroy();
	FTransform restartPoint;
	restartPoint.SetLocation(FVector(-510, 550, 191));
		UE_LOG(LogTemp, Log, TEXT("Respone O"));
		respawnplayer->SetActorLocation(FVector(-510, 550, 191));
		AOValTanCharacter* AOvalC = (AOValTanCharacter*)respawnplayer;
		AOvalC->HP_Cur = AOvalC->HP_Max;
		AOvalC->isDead = false;
			AOValTanCharacter* OvalC = Cast<AOValTanCharacter>(respawnplayer);
			if (OvalC != nullptr)
			{
				OvalC->Mesh3P->SetVisibility(true);
			}
		Possess(respawnplayer);
}

void ANetPlayerController::MultiChangePlayerToSpectator_Implementation()
{

}

void ANetPlayerController::ServerChangePlayerToSpectator_Implementation()
{
	respawnplayer = GetPawn();
	//UnPossess();

	if (Spec != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UE_LOG(LogTemp, Warning, TEXT("respawnPlayer is %s"), respawnplayer != nullptr ? *respawnplayer->GetName() : *FString("NuLL"));
		if (respawnplayer == nullptr)
		{
			return;
		}
		ASpectatorPawn* spectator = GetWorld()->SpawnActor<ASpectatorPawn>(Spec, respawnplayer->GetTransform(), param);
		if (spectator != nullptr)
		{
			// ������ ������ ���� �����Ѵ�.
			Possess(spectator);
			// 5�� �ڿ� �������Ѵ�.
			FTimerHandle respawnHandle;
			FTimerHandle VisbleHandle;
			GetWorldTimerManager().SetTimer(VisbleHandle, this, &ANetPlayerController::ServerChangePlayerHidden, 2.0f, false);
			GetWorldTimerManager().SetTimer(respawnHandle, this, &ANetPlayerController::ServerRespawnPlayer_Implementation, 5.0f, false);
		}
	}
}

void ANetPlayerController::ServerChangePlayerHidden_Implementation()
{
	if (respawnplayer!=nullptr)
	{
		MultiChangePlayerHidden(respawnplayer);
	}
}

void ANetPlayerController::MultiChangePlayerHidden_Implementation(APawn* HiddenPlayer)
{
	if (HiddenPlayer != nullptr)
	{
		AOValTanCharacter* OvalC = Cast<AOValTanCharacter>(HiddenPlayer);
		if (OvalC != nullptr)
		{
			OvalC->Mesh3P->SetVisibility(false);
		}
	}
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
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPTracer, player->GetTransform(), param);

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
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPGenji, player->GetTransform(), param);
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


void ANetPlayerController::MultiRespawnPlayer_Implementation()
{
	if (IsLocalController())
	{
			APawn* playerPawn = GetPawn();
			UnPossess();
			playerPawn->Destroy();
			FTransform restartPoint;
			restartPoint.SetLocation(FVector(-510, 550, 191));
			UE_LOG(LogTemp, Log, TEXT("Respone x"));
			if (respawnplayer != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("Respone O"));
				respawnplayer->SetActorLocation(FVector(-510, 550, 191));
				AOValTanCharacter* AOvalC = (AOValTanCharacter*)respawnplayer;
				AOvalC->HP_Cur = AOvalC->HP_Max;
				Possess(respawnplayer);
			}
	}
}

void ANetPlayerController::ChangeUIGameStart_Implementation(int32 index)
{
	if (IsLocalController())
	{
		APawn* playerPawn = GetPawn();
		if (playerPawn!=nullptr)
		{
			AOValTanCharacter* OvalPawn = Cast<AOValTanCharacter>(playerPawn);
			if (OvalPawn!=nullptr)
			{
				OvalPawn->Ingame_UI->SwitchCanvas(index);
				if (index==3)
				{
					OvalPawn->Ingame_UI->CountDown();
				}
			}
		}
	}
}

