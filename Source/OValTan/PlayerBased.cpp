// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBased.h"


void APlayerBased::Attack1()
{
	UE_LOG(LogTemp, Log, TEXT("child attack1"));
}

void APlayerBased::Attack2()
{
	UE_LOG(LogTemp, Log, TEXT("child attack2"));
}

void APlayerBased::Skill1()
{
	UE_LOG(LogTemp, Log, TEXT("child Skill1"));
}

void APlayerBased::Skill2()
{
	UE_LOG(LogTemp, Log, TEXT("child Skill2"));
}

void APlayerBased::Ultimate()
{
	UE_LOG(LogTemp, Log, TEXT("child Ulti"));
}

void APlayerBased::Reload()
{
	UE_LOG(LogTemp, Log, TEXT("child Reload"));
}

void APlayerBased::MeleeAttack()
{
	UE_LOG(LogTemp, Log, TEXT("child Melee"));
}
