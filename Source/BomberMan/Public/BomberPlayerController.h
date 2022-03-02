// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BomberPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABomberPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void MoveVertical(float AxisValue);

	void MoveHorizontal(float AxisValue);

	void SpawnBombInput();

	virtual void SetupInputComponent() override;

	void RemoteDetonateInput();

	APawn* Pawn;

};
