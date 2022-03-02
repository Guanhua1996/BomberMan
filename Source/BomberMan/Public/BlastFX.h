// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlastFX.generated.h"

UCLASS()
class BOMBERMAN_API ABlastFX : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlastFX();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BlastFXSM;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;

	FTimerHandle TimerHandle_Destroy;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DelayDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupBlast(FVector StartPos,FVector EndPos);

};
