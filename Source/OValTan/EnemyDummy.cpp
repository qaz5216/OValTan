// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDummy.h"
#include "EnemyWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Components/ProgressBar.h>


void AEnemyDummy::Damged(int32 Value)
{
	if (HP_Cur-Value>0)
	{
		HP_Cur = HP_Cur - Value;
	}
	else
	{
		HP_Cur = 0;
		Die();
	}

}

void AEnemyDummy::Die()
{
	Destroy();
}
