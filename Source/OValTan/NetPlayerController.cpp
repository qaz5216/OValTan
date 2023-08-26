// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerController.h"
#include "BattleGameModeBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "OValTanCharacter.h"
#include "UIBase.h"
#include "Net/UnrealNetwork.h"
#include "NetPlayerState.h"

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
		UE_LOG(LogTemp, Log, TEXT("Respone O"));
		AOValTanCharacter* AOvalC = (AOValTanCharacter*)respawnplayer;
		AOvalC->HP_Cur = AOvalC->HP_Max;
		AOvalC->isDead = false;
			AOValTanCharacter* OvalC = Cast<AOValTanCharacter>(respawnplayer);
			if (OvalC != nullptr)
			{
				OvalC->Mesh3P->SetVisibility(true);
				OvalC->Mesh3P->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				int32 RandSpawn=FMath::RandRange(0,1);
				switch (RandSpawn)
				{
				case 0 :
					respawnplayer->SetActorLocation(FVector(-608, -1489, 191));
					UE_LOG(LogTemp,Warning,TEXT("0caseRespawn"));
					break;
				case 1 :
					respawnplayer->SetActorLocation(FVector(-4950, -1092, 191));
					UE_LOG(LogTemp, Warning, TEXT("1caseRespawn"))
					break;
				default:
					break;
				}
			}
		Possess(respawnplayer);
		AOvalC->MultiDamaged(AOvalC->HP_Cur);
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
		AOValTanCharacter* DestChar = Cast<AOValTanCharacter>(player);
		DestChar->DetachUI();
		UnPossess();
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPTracer, player->GetTransform(), param);
		if (Charactor != nullptr)
		{
			//DestChar->Ingame_UI->RemoveFromParent();
			MultiChangePlayerToTracer();
			Possess(Charactor);
			Charactor->AttachUI();
			Charactor->Ingame_UI->UI_HP_Cur=Charactor->HP_Max;
			if (DestChar!=nullptr)
			{
				//MultiChangePlayerToTracer();
			}
			UE_LOG(LogTemp, Warning, TEXT("-----------------------------------NetMode : %d"), GetNetMode());
		}
	// �÷��̾ �����Ѵ�.

		player->Destroy();
}

void ANetPlayerController::MultiChangePlayerToTracer_Implementation()
{
	ANetPlayerState* Nps = GetPlayerState<ANetPlayerState>();
	Nps->charnum = 2;
}

void ANetPlayerController::ServerChangePlayerToGenji_Implementation()
{

	APawn* player = GetPawn();
	AOValTanCharacter* DestChar = Cast<AOValTanCharacter>(player);
	DestChar->DetachUI();
	UnPossess();
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AOValTanCharacter* Charactor = GetWorld()->SpawnActor<AOValTanCharacter>(BPGenji, player->GetTransform(), param);
	if (Charactor != nullptr)
	{
		//DestChar->Ingame_UI->RemoveFromParent();
		Possess(Charactor);
		MultiChangePlayerToGenji();
		Charactor->AttachUI();
		Charactor->Ingame_UI->UI_HP_Cur = Charactor->HP_Max;
		if (DestChar != nullptr)
		{
			//MultiChangePlayerToTracer();
		}
		UE_LOG(LogTemp, Warning, TEXT("-----------------------------------NetMode : %d"), GetNetMode());
	}
	// �÷��̾ �����Ѵ�.

	player->Destroy();

}


void ANetPlayerController::MultiChangePlayerToGenji_Implementation()
{
	ANetPlayerState* Nps = GetPlayerState<ANetPlayerState>();
	Nps->charnum = 1;
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

void ANetPlayerController::ChangeUIGameEnd_Implementation()
{
	if (IsLocalController())
	{
		APawn* playerPawn = GetPawn();
		if (playerPawn != nullptr)
		{
			AOValTanCharacter* OvalPawn = Cast<AOValTanCharacter>(playerPawn);
			if (OvalPawn != nullptr)
			{
				OvalPawn->Ingame_UI->SwitchCanvas(4);
			}
		}
	}
}

void ANetPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerController,bishost);
}