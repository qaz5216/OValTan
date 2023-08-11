// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OValTanCharacter.h"
#include "Tracer.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API ATracer : public AOValTanCharacter
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void Attack1();
	UFUNCTION(BlueprintImplementableEvent)
	void Attack2();
	UFUNCTION(BlueprintImplementableEvent)
	void Skill1();
	UFUNCTION(BlueprintImplementableEvent)
	void Skill2();
	UFUNCTION(BlueprintImplementableEvent)
	void Ultimate();
	UFUNCTION(BlueprintImplementableEvent)
	void Reload();
	UFUNCTION(BlueprintImplementableEvent)
	void MeleeAttack();


};
