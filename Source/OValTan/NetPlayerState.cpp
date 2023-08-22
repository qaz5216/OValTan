// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerState.h"
#include "NetGameInstance.h"
#include "NetGameStateBase.h"
#include "OValTanCharacter.h"
#include "UIBase.h"


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
	if (NewScore > 5)
	{
		if (HasAuthority())
		{
			TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
			for (APlayerState* p : players)
			{
				AOValTanCharacter* playerpawn = p->GetPawn<AOValTanCharacter>();
				if (playerpawn != nullptr)
				{
					p->SetScore(0);
					if (playerpawn->GetController()->IsLocalPlayerController())
					{
						GetWorld()->GetGameState<ANetGameStateBase>()->bGameStart = false;
						playerpawn->Ingame_UI->SwitchCanvas(3);
						if (playerpawn->Victory_UI)
						{
								playerpawn->Victory_UI->AddToViewport();
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Loserzzz"));
					}
				}
			}
		}
	}
}

