// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OValTanCharacter.h"
#include "EnemyDummy.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API AEnemyDummy : public AOValTanCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Damged(int32 Value);
	void Die();
};
