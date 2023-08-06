// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OValTanCharacter.h"
#include "Genji.generated.h"

/**
 * 
 */
UCLASS()
class OVALTAN_API AGenji : public AOValTanCharacter
{
	GENERATED_BODY()
public:
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

	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=CharacterSetting)
	//int32 HP_Cur;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=CharacterSetting)
	//int32 HP_Max=200;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=CharacterSetting)
	//float CoolTime_Skill1_Cur=0;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=CharacterSetting)
	//float CoolTime_Skill2_Cur=0;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=CharacterSetting)
	//float Gauge_Ultimate_Cur=0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=CharacterSetting)
	//float CoolTime_Skill1_Max;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=CharacterSetting)
	//float CoolTime_Skill2_Max;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=CharacterSetting)
	//float Gauge_Ultimate_Max;
};
