// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OValTanCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AOValTanCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Replicated ,Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Replicated, Category=Mesh)
	USkeletalMeshComponent* Mesh3P;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Replicated, Category=Mesh)
	UCapsuleComponent* HeadComp;



	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category=Input)
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* Attack1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* Attack2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* Skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* Skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* UltimateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MeleeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* button1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* button2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* TabAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* TestAction;



	//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sound, meta=(AllowPrivateAccess = "true"))
	class USoundBase* CooltimeSound;




public:
	AOValTanCharacter();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
public:

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:
	//���ε�� �Լ� ������ ��������
		//void BindMove(const FInputActionValue& Value);
		//void BindLook(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);
	UFUNCTION(Server,Reliable)
	void BindMove(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	UFUNCTION(Server,Reliable)
	void BindLook(const FInputActionValue& Value);
	UFUNCTION(Server,Reliable)
	void BindAttack1();
	UFUNCTION(Server,Reliable)
	void BindAttack2();
	UFUNCTION(Server,Reliable)
	void BindSkill1();
	UFUNCTION(Server,Reliable)
	void BindSkill2();
	UFUNCTION(Server,Reliable)
	void BindUltimate();
	UFUNCTION(Server,Reliable)
	void BindReload();
	UFUNCTION(Server,Reliable)
	void BindMeleeAttack();
	UFUNCTION(Server,Reliable)
	void BindButton1();
	UFUNCTION(Server,Reliable)
	void BindButton2();
	
	//�ɱ�
	void StartSit();
	void StopSit();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	bool bisSit=false;

	//�ڽĿ� �Լ�
	virtual void Attack1();// �������Ʈ assignable?? 
	virtual void Attack2();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Ultimate();
	virtual void Reload();
	virtual void MeleeAttack();
	virtual void Button1();
	virtual void Button2();

	UFUNCTION(Server,BlueprintCallable,Reliable)
	void newDamaged(int32 Value);
	virtual void Die();
	
	UFUNCTION(Server,BlueprintCallable,Reliable)
	void Killing();

	UFUNCTION(NetMulticast,Reliable)
	void VictoryUI(bool Victory);

	UPROPERTY(Replicated)
	class APlayerController* Mycontroller;
	//UI System
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category=UI)
	TSubclassOf<class UUIBase> Ingame_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category=UI)
	class UUIBase* Ingame_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category=UI)
	TSubclassOf<class UUserWidget> Victory_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category=UI)
	class UUserWidget* Victory_UI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = CharacterSetting)
	int32 HP_Cur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	int32 HP_Max=100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = CharacterSetting)
	int32 Ammo_Cur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	int32 Ammo_Max=24;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float CoolTime_Skill1_Cur=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float CoolTime_Skill2_Cur=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float Gauge_Ultimate_Cur=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float CoolTime_Skill1_Max=5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float CoolTime_Skill2_Max=10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	bool bCanSkill1 = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	bool bCanSkill2 = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=CharacterSetting)
	float Gauge_Ultimate_Max=100;

	void PrintLog();

	void TabShow();
	void TabClose();

	void Test();
	void MyDestroy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = CharacterSetting)
	bool isDead = false;
private:
	enum ENetRole myLocalRole;
	enum ENetRole myRemoteRole;
};

