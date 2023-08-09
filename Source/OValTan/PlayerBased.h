// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OValTanCharacter.h"
#include "PlayerBased.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API APlayerBased : public AOValTanCharacter
{
	GENERATED_BODY()
	void Attack1();
	void Attack2();
	void Skill1();
	void Skill2();
	void Ultimate();
	void Reload();
	void MeleeAttack();
};
