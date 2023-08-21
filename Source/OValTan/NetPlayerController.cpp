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

// 재시작 함수
void ANetPlayerController::ServerRespawnPlayer_Implementation()
{
	MutiRespawnPlayer(gm);
}

void ANetPlayerController::ServerChangePlayerToSpectator_Implementation()
{
		MutiChangePlayerToSpectator(gm);
}

void ANetPlayerController::ServerChangePlayerToTracer_Implementation()
{
	APawn* player = GetPawn();
	UnPossess();

	// 관전자 폰을 생성한다.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPTracer,player->GetTransform(), param);

		if (Charactor != nullptr)
		{
			// 생성된 관전자 폰에 빙의한다.
			Possess(Charactor);
		}
	}

	// 플레이어를 제거한다.
	
	player->Destroy();
}

void ANetPlayerController::ServerChangePlayerToGenji_Implementation()
{
	APawn* player = GetPawn();
	UnPossess();
	UE_LOG(LogTemp, Warning, TEXT("Button-Warning-1"));
	// 관전자 폰을 생성한다.
	if (gm != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPGenji,player->GetTransform(), param);
		UE_LOG(LogTemp, Warning, TEXT("Button-Warning-2"));
		if (Charactor != nullptr)
		{

			UE_LOG(LogTemp, Warning, TEXT("Button-Warning-3"));
			// 생성된 관전자 폰에 빙의한다.
			Possess(Charactor);
		}
	}

	// 플레이어를 제거한다.
	player->Destroy();

}

void ANetPlayerController::MutiChangePlayerToSpectator_Implementation(ABattleGameModeBase* ggm)
{
	if (IsLocalController())
	{
		respawnplayer = GetPawn();
		UnPossess();
		
		if (ggm != nullptr)
		{
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ASpectatorPawn* spectator = GetWorld()->SpawnActor<ASpectatorPawn>(ggm->SpectatorClass, respawnplayer->GetTransform(), param);
			if (spectator != nullptr)
			{
				// 생성된 관전자 폰에 빙의한다.
				Possess(spectator);
			}
		}
		// 5초 뒤에 리스폰한다.
		FTimerHandle respawnHandle;

		GetWorldTimerManager().SetTimer(respawnHandle, this, &ANetPlayerController::ServerRespawnPlayer_Implementation, 5.0f, false);
	}
}

void ANetPlayerController::MutiRespawnPlayer_Implementation(ABattleGameModeBase* ggm)
{
	if (IsLocalController())
	{
		if (ggm != nullptr)
		{
			APawn* playerPawn = GetPawn();
			UnPossess();
			playerPawn->Destroy();
			// 처음 배정받은 PlayerStart 액터 위치에서 리스폰
			//gm->RestartPlayer(this);

			// 지정된 Transform에서 리스폰
			FTransform restartPoint;
			restartPoint.SetLocation(FVector(-510, 550, 191));
			if (respawnplayer != nullptr)
			{
				respawnplayer->SetActorLocation(FVector(-510, 550, 191));
				Possess(respawnplayer);
			}
			else
			{
				AOValTanCharacter* AOvalC = (AOValTanCharacter*)respawnplayer;
				AOvalC->HP_Cur = AOvalC->HP_Max;
				ggm->RestartPlayerAtTransform(this, restartPoint);
			}
		}
	}
}
