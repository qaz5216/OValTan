// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HillPack.generated.h"

UCLASS()
class OVALTAN_API AHillPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHillPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Replicated ,Category=Mesh)
	UStaticMeshComponent* HillComp;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Replicated ,Category=Mesh)
	UStaticMesh* HillMesh;
};
