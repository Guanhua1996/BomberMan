// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnbreakableBlock.generated.h"

UCLASS()
class BOMBERMAN_API AUnbreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnbreakableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, Category = "Component");
	UStaticMeshComponent* UnbreakableBlockSM;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
