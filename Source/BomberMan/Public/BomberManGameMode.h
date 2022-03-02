// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberManGameMode.generated.h"

enum class EPowerUpType :uint8 {
	SpeedBoost,	//��������
	MoreBombs,	//ը����������
	LongerBlast,	//��ը��Χ����
	RemoteBomb	//ң��ը��
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
	float TotalTime = 300.0f; //����ʱ300��

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
