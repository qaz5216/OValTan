// Copyright Epic Games, Inc. All Rights Reserved.

#include "OValTanCharacter.h"
#include "OValTanProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TP_WeaponComponent.h"
#include "InputMappingContext.h"
#include "UIBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"
#include "NetPlayerController.h"
#include <UMG/Public/Components/TextBlock.h>
#include "NetPlayerState.h"
#include "NetGameStateBase.h"
#include "EnemyDummy.h"
//////////////////////////////////////////////////////////////////////////
// AOValTanCharacter

AOValTanCharacter::AOValTanCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// 3인칭 메쉬 추가욧
	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh3P"));
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetupAttachment(RootComponent);
	Mesh3P->bCastDynamicShadow = false;
	Mesh3P->CastShadow = false;
	//Mesh3P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh3P->SetRelativeLocation(FVector(0.f,0.f, -100));

	// 헤드 콜리전추가욧
	HeadComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HeadComp"));
	HeadComp->SetupAttachment(GetMesh3P());
	HeadComp->SetRelativeLocation(FVector(0,0,170));
	// Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>TempMapping
	(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FirstPerson/Input/IMC_Default.IMC_Default'"));
	if (TempMapping.Succeeded())
	{
		DefaultMappingContext = TempMapping.Object;
	}
	//Input Context Bind
	ConstructorHelpers::FObjectFinder<UInputAction>TempJump(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Jump.IA_Jump'"));
	if (TempJump.Succeeded())
	{
		JumpAction = TempJump.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempMove(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Move.IA_Move'"));
	if (TempMove.Succeeded())
	{
		MoveAction = TempMove.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempLook(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Look.IA_Look'"));
	if (TempLook.Succeeded())
	{
		LookAction = TempLook.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempAttack1(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Attack1.IA_Attack1'"));
	if (TempAttack1.Succeeded())
	{
		Attack1Action = TempAttack1.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction>TempAttack2(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Attack2.IA_Attack2'"));
	if (TempAttack2.Succeeded())
	{
		Attack2Action = TempAttack2.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempSkill1(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Skill1.IA_Skill1'"));
	if (TempSkill1.Succeeded())
	{
		Skill1Action = TempSkill1.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempSkill2(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Skill2.IA_Skill2'"));
	if (TempSkill2.Succeeded())
	{
		Skill2Action = TempSkill2.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempUltimate(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Ultimate.IA_Ultimate'"));
	if (TempUltimate.Succeeded())
	{
		UltimateAction = TempUltimate.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempMeleeAttack(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_MeleeAttack.IA_MeleeAttack'"));
	if (TempMeleeAttack.Succeeded())
	{
		MeleeAttackAction = TempMeleeAttack.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempSit(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Sit.IA_Sit'"));
	if (TempSit.Succeeded())
	{
		SitAction = TempSit.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempReload(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Reload.IA_Reload'"));
	if (TempReload.Succeeded())
	{
		ReloadAction = TempReload.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction>TempButton1(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_1button.IA_1button'"));
	if (TempButton1.Succeeded())
	{
		button1Action = TempButton1.Object;
	}	ConstructorHelpers::FObjectFinder<UInputAction>TempButton2(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_2button.IA_2button'"));
	if (TempButton2.Succeeded())
	{
		button2Action = TempButton2.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction>TempTab(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Tab.IA_Tab'"));
	if (TempTab.Succeeded())
	{
		TabAction = TempTab.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction>TempTest(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Test.IA_Test'"));
	if (TempTest.Succeeded())
	{
		TestAction = TempTest.Object;
	}



	//사운드 쿨타임완료 
	ConstructorHelpers::FObjectFinder<USoundBase>TempCoolsound(TEXT("/Script/Engine.SoundWave'/Game/SFX/SFX_UI/SFX_SkillReady.SFX_SkillReady'"));
	if (TempCoolsound.Succeeded())
	{
		CooltimeSound = TempCoolsound.Object;
	}


	//HP 초기세팅
	HP_Cur = HP_Max;
	//Ammo 초기세팅
	Ammo_Cur = Ammo_Max;

	bReplicates = true;
}

void AOValTanCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	myLocalRole = GetLocalRole();
	myRemoteRole = GetRemoteRole();
	Victory_UI = CreateWidget<UUserWidget>(GetWorld(), Victory_Widget);
}

void AOValTanCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Skill1 Cool
	if (!bCanSkill1)
	{
		if (CoolTime_Skill1_Cur>0)
		{
			CoolTime_Skill1_Cur -= DeltaSeconds;
		}
		else 
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CooltimeSound);
			bCanSkill1 = true;
			CoolTime_Skill1_Cur = 0;
		}
	}
	//Skill2 Cool
	if (!bCanSkill2)
	{
		if (CoolTime_Skill2_Cur>0)
		{
			CoolTime_Skill2_Cur -= DeltaSeconds;
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CooltimeSound);
			bCanSkill2 = true;
			CoolTime_Skill2_Cur = 0;
		}
	}
	//PrintLog();
}



//////////////////////////////////////////////////////////////////////////// Input

void AOValTanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::Look);

		//Attack
		EnhancedInputComponent->BindAction(Attack1Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindAttack1);
		EnhancedInputComponent->BindAction(Attack2Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindAttack2);
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindSkill1);
		EnhancedInputComponent->BindAction(Skill2Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindSkill2);
		EnhancedInputComponent->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindUltimate);
		EnhancedInputComponent->BindAction(MeleeAttackAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindMeleeAttack);

		//앉기
		EnhancedInputComponent->BindAction(SitAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::StartSit);
		EnhancedInputComponent->BindAction(SitAction, ETriggerEvent::Completed, this, &AOValTanCharacter::StopSit);
		//재장전
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindReload);


		//캐릭터 스위칭
		EnhancedInputComponent->BindAction(button1Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindButton1);
		EnhancedInputComponent->BindAction(button2Action, ETriggerEvent::Triggered, this, &AOValTanCharacter::BindButton2);

		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::TabShow);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Completed, this, &AOValTanCharacter::TabClose);

		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &AOValTanCharacter::Test);

	}
}

//바인드용 함수 점프는 제외했음
void AOValTanCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (bisSit) {
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y/2);
			AddMovementInput(GetActorRightVector(), MovementVector.X/2);

		}
		else {
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);

		}
	}
}

void AOValTanCharacter::BindMove_Implementation(const FInputActionValue& Value)
{
	Move(Value);
}

void AOValTanCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	APlayerController* pc = GetController<APlayerController>();
}

void AOValTanCharacter::BindLook_Implementation(const FInputActionValue& Value)
{
	Look(Value);
}

void AOValTanCharacter::BindAttack1_Implementation()
{
	Attack1();
}

void AOValTanCharacter::BindAttack2_Implementation()
{
	Attack2();
}

void AOValTanCharacter::BindSkill1_Implementation()
{
	if (bCanSkill1)
	{
		UE_LOG(LogTemp, Log, TEXT("Skill1 Not Cool"));
		UE_LOG(LogTemp, Log, TEXT("Skill1 CoolTimemax:%f"), CoolTime_Skill1_Max);
		bCanSkill1 = false;
		CoolTime_Skill1_Cur = CoolTime_Skill1_Max;
		Skill1();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Skill1 Cool:%f"),CoolTime_Skill1_Cur);
	}
}

void AOValTanCharacter::BindSkill2_Implementation()
{
	if (bCanSkill2)
	{
		bCanSkill2 = false;
		CoolTime_Skill2_Cur = CoolTime_Skill2_Max;
		Skill2();
	}
}

void AOValTanCharacter::BindUltimate_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Cur UltGage:%f"), Gauge_Ultimate_Cur);
	Ultimate();
}

void AOValTanCharacter::BindReload_Implementation()
{
	Ammo_Cur = Ammo_Max;
	Reload();
}

void AOValTanCharacter::BindMeleeAttack_Implementation()
{
	MeleeAttack();
}

void AOValTanCharacter::BindButton1_Implementation()
{
	ANetPlayerController* Npc=GetController<ANetPlayerController>();
	Button1();
	Npc->ServerChangePlayerToGenji();
}

void AOValTanCharacter::BindButton2_Implementation()
{
	ANetPlayerController* Npc = GetController<ANetPlayerController>();
	Button2();
	Npc->ServerChangePlayerToTracer();
}


//앉기
void AOValTanCharacter::StartSit()
{
	if (!bisSit)
	{
		bisSit = true;
		FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 0.0f)); // Position the camera
		UE_LOG(LogTemp, Log, TEXT("SitStart"));

	}
}

void AOValTanCharacter::StopSit()
{
	bisSit = false;
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	UE_LOG(LogTemp, Log, TEXT("SitStop"));
}

//자식용함수

void AOValTanCharacter::Attack1()
{
	UE_LOG(LogTemp, Log, TEXT("parent attack1"));
}



void AOValTanCharacter::Attack2()
{
	UE_LOG(LogTemp, Log, TEXT("parent attack2"));
}

void AOValTanCharacter::Skill1()
{
	UE_LOG(LogTemp, Log, TEXT("parent Skill1"));
}

void AOValTanCharacter::Skill2()
{
	UE_LOG(LogTemp, Log, TEXT("parent Skill2"));
}

void AOValTanCharacter::Ultimate()
{
	UE_LOG(LogTemp, Log, TEXT("parent Ult"));
}

void AOValTanCharacter::Reload()
{
	ANetGameStateBase* Gs=GetWorld()->GetGameState<ANetGameStateBase>();
	if (Gs!=nullptr)
	{
		Gs->bGameStart = true;
		UE_LOG(LogTemp,Warning,TEXT("GameStart!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Sorry"));
	}
}

void AOValTanCharacter::MeleeAttack()
{
	UE_LOG(LogTemp, Log, TEXT("parent MeleeA"));
}

void AOValTanCharacter::Button1()
{
	UE_LOG(LogTemp, Log, TEXT("parent MeleeA"));
}

void AOValTanCharacter::Button2()
{
	UE_LOG(LogTemp, Log, TEXT("parent MeleeA"));
}

void AOValTanCharacter::newDamaged_Implementation(int32 Value)
{
	if (HP_Cur-Value>0)
	{
		HP_Cur = HP_Cur - Value;
	}
	else
	{
		HP_Cur = 0;
		UE_LOG(LogTemp, Log, TEXT("DieCall"));
		AEnemyDummy* EnemyDummy = Cast<AEnemyDummy>(this);
		if (EnemyDummy!=nullptr)
		{
			if (!isDead){
				isDead = true;
				FTimerHandle DestroyHandle;
				GetWorld()->GetTimerManager().SetTimer(DestroyHandle,this,&AOValTanCharacter::MyDestroy, 5.0f, false);
			}
		}
		else
		{

		if (!isDead)
		{
			isDead = true;
			ANetPlayerController* Npc = GetController<ANetPlayerController>();
			Npc->ServerChangePlayerToSpectator();
		}

		}
	}
}



void AOValTanCharacter::Die()
{

}

void AOValTanCharacter::Killing_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KillingCall"));
	ANetPlayerState* ps = GetPlayerState<ANetPlayerState>();
	ANetGameStateBase* gs = GetWorld()->GetGameState<ANetGameStateBase>();
	if (ps!=nullptr&&gs->bGameStart)
	{
		if (ps->GetScore() + 1<=5)
		{
			UE_LOG(LogTemp,Warning,TEXT("%d"), (int32)ps->GetScore() + 1);
			ps->SetKillScore(ps->GetScore() + 1);
			if (ps->GetScore()==5)
			{
				TArray<APlayerState*> players = GetWorld()->GetGameState<ANetGameStateBase>()->GetPlayerArrayByScore();
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
								if (playerpawn->GetController()->GetName().Equals(Controller->GetName())) {
									playerpawn->VictoryUI(true);
								}
								else
								{
									playerpawn->VictoryUI(false);
								}
							}
						}
					}
				}
			}
		}
	}
}

void AOValTanCharacter::VictoryUI_Implementation(bool Victory)
{
if (Controller!=nullptr)
{
	if (Controller->IsLocalController())
	{
		if (Victory)
		{
			Victory_UI->AddToViewport();
		}
		else
		{
			Ingame_UI->SwitchCanvas(4);
		}
	}
}
}

void AOValTanCharacter::PrintLog()
{
	const FString localRoleString = UEnum::GetValueAsString<ENetRole>(myLocalRole);
	const FString remoteRoleString = UEnum::GetValueAsString<ENetRole>(myRemoteRole);
	const FString ownerString = GetOwner() != nullptr ? GetOwner()->GetName() : FString("No Owner");
	const FString connectionString = GetNetConnection() != nullptr ? FString("Valid Connection") : FString("Invalid Connection");
	const FString printString = FString::Printf(TEXT("Local Role: %s\nRemote Role: %s\nOwner Name: %s\nNet Connection : %s"), *localRoleString, *remoteRoleString, *ownerString, *connectionString);
	DrawDebugString(GetWorld(), GetActorLocation(), printString, nullptr, FColor::White, 0, true);
}

void AOValTanCharacter::TabShow()
{
	if (Ingame_UI!=nullptr)
	{
		Ingame_UI->text_players->SetVisibility(ESlateVisibility::Visible);
	}
	//Killing();
}

void AOValTanCharacter::TabClose()
{
	if (Ingame_UI != nullptr)
	{
		Ingame_UI->text_players->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AOValTanCharacter::Test()
{
	ANetPlayerController* Npc = GetController<ANetPlayerController>();
	Npc->ServerChangePlayerToSpectator();
}

void AOValTanCharacter::MyDestroy()
{
	Destroy();
}

void AOValTanCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AOValTanCharacter::GetHasRifle()
{
	return bHasRifle;
}


void AOValTanCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOValTanCharacter, Mesh3P);
	DOREPLIFETIME(AOValTanCharacter, HP_Cur);
	DOREPLIFETIME(AOValTanCharacter, CoolTime_Skill1_Cur);
	DOREPLIFETIME(AOValTanCharacter, CoolTime_Skill2_Cur);
	DOREPLIFETIME(AOValTanCharacter, Gauge_Ultimate_Cur);
}