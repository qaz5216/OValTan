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
protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
public:
	void Die() override;
	UPROPERTY(BlueprintReadWrite)
	bool bDieDummy = false;
	float curtime = 0;
};
