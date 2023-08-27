// Fill out your copyright notice in the Description page of Project Settings.


#include "HillPack.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AHillPack::AHillPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HillComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	HillComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh
	(TEXT("/Script/Engine.StaticMesh'/Game/Art/last3_Object002.last3_Object002'"));
	if (TempMesh.Succeeded())
	{
		HillMesh = TempMesh.Object;
	}
	HillComp->SetStaticMesh(HillMesh);

}

// Called when the game starts or when spawned
void AHillPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHillPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHillPack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHillPack, HillComp);
	DOREPLIFETIME(AHillPack, HillMesh);
}