// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerState.h"
#include "NetGameInstance.h"
#include "NetGameStateBase.h"
#include "OValTanCharacter.h"
#include "UIBase.h"
#include "NetPlayerController.h"


void ANetPlayerState::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UNetGameInstance>(GetGameInstance());

	if (gi != nullptr && GetPlayerController() != nullptr && GetPlayerController()->IsLocalPlayerController())
	{
		SetMyName(gi->mySessionName);
	}
}

void ANetPlayerState::SetMyName_Implementation(const FString& myName)
{
	SetPlayerName(myName);
}

void ANetPlayerState::SetKillScore_Implementation(float NewScore)
{
	SetScore(NewScore);
	if (NewScore == 5)
	{
		GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = false;
		//UE_LOG(LogTemp, Warning, TEXT("GOEndUI"));
		/*TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
		for (APlayerState* p : players)
		{
			if (p->GetPawn<AOValTanCharacter>())
			{
				AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
				if (playerpawn != nullptr)
				{
					if (playerpawn->GetController() != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("local???"));
						if (playerpawn->GetController()->GetName().Equals(VictoryNpc->GetName())) {
							UE_LOG(LogTemp, Warning, TEXT("local!!"));
							playerpawn->Ingame_UI->SwitchCanvas(3);
							if (playerpawn->Victory_UI)
							{
								playerpawn->Victory_UI->AddToViewport();
							}
						}
						else
						{
							ANetPlayerController* Npc = playerpawn->GetController<ANetPlayerController>();
							Npc->ChangeUIGameEnd();
						}
					}
				}
			}
		}*/
	}
}

void ANetPlayerState::SetEndUI_Implementation()
{
		UE_LOG(LogTemp, Warning, TEXT("EndUIStart"));
		
}

