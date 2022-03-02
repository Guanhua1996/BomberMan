// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberManGameMode.generated.h"

enum class EPowerUpType :uint8 {
	SpeedBoost,	//移速增加
	MoreBombs,	//炸弹上限增加
	LongerBlast,	//爆炸范围增加
	RemoteBomb	//遥控炸弹
};

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABomberManGameMode : public AGameModeBase
{
	GENERATED_BODY()
		ABomberManGameMode();

	
protected:
	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float DropChance = 0.4;

	UPROPERTY(EditAnyWhere, Category = "Time")
	float TotalTime = 300.0f; //倒计时300秒

	FText TimeText;

	class UBomberHUD* BomberHUD;

	virtual void BeginPlay() override;

	class UBomberSaveGame* BomberSaveInstance;

	FString SaveSlotName = "MatchValue";

	int UserIndex = 0;

	void IncrementP1Victories();

	void IncrementP2Victories();

	void UpdateScore();

	void OnGameEnd();

public:

	FORCEINLINE float GetDropChance() { return DropChance; }

	virtual void Tick(float DeltaSeconds) override;

	void OnPlayerDeath(AController* Controller);

	void Restart();
};
