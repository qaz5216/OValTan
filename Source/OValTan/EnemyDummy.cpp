// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDummy.h"
#include "EnemyWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Components/ProgressBar.h>
#include <Components/CapsuleComponent.h>

#include <Components/SkeletalMeshComponent.h>

void AEnemyDummy::BeginPlay()
{
	Super::BeginPlay();
	bDieDummy = false;
	curtime = 0;
}

void AEnemyDummy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bDieDummy)
	{
		curtime += DeltaSeconds;
		if (curtime>5&&bSetVisible)
		{
			Mesh3P->SetVisibility(false);
			bSetVisible = false;
			Mesh3P->PlayAnimation(IdleAnim,true);
		}
		if (curtime>10)
		{
			HP_Cur = HP_Max;
			Mesh3P->SetVisibility(true);
			Mesh3P->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			HeadComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			bDieDummy = false;
			bSetVisible = true;
			curtime = 0;
		}
	}
}

void AEnemyDummy::Die()
{
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HeadComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDieDummy = true;
}
