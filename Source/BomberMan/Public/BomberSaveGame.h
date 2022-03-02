// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BomberSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBomberSaveGame : public USaveGame
{
	GENERATED_BODY()
protected:
	

	UBomberSaveGame();

public:

	UPROPERTY()
		int P1_Victories;
	UPROPERTY()
		int P2_Victories;

	FORCEINLINE int GetP1Victories() { return P1_Victories; }
	FORCEINLINE int GetP2Victories() { return P2_Victories; }

	void IncreaseP1Victories() { P1_Victories++; }
	void IncreaseP2Victories() { P2_Victories++; }
};
