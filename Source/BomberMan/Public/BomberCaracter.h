// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BomberManGameMode.h"
#include "BomberCaracter.generated.h"

class ABomb;

UCLASS()
class BOMBERMAN_API ABomberCaracter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABomberCaracter();

protected:

	UPROPERTY(EditAnyWhere, Category = "Bomb")
	TSubclassOf<ABomb> Bomb;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float GetSnappedValue(int Value, float Scale);

	FVector GetSnappedPosition(FVector SourcePos);

	float InitialBlastRange = 1.0f;

	int InitialBombLimit = 1;

	float InitialMaxWalkSpeed = 450.0f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
		int SpeedReduce = 100;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
		float BlastRangeReduce = 1;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
		int BombLimitReduce = 1;

	float BlastRange = 1.0f;	//±¨’®∑∂Œß

	int BombLimit = 1;	//’®µØ…œœﬁ

	TArray<class ABomb*> PlacedBombs;

	bool bHasRemote = false;

	class ABomberManGameMode* GameMode;

	bool bHasDead = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnBomb();

	void IncreaseBlastRange(float BlastRangeBoost) { this->BlastRange += BlastRangeBoost; }

	void PlaceBomb(ABomb* TBomb) { this->PlacedBombs.Add(TBomb); }

	void RemoveBomb(ABomb* TBomb) { this->PlacedBombs.Remove(TBomb); }

	int PlacedBombsNum() { return PlacedBombs.Num(); }

	ABomb* GetPlacedBomb(int i) { return PlacedBombs[i]; }

	void IncreaseBombLimit(int BombLimitBoost) { this->BombLimit += BombLimitBoost; }

	void SetBHasRemoteTrue() { bHasRemote = true; }

	FORCEINLINE int GetBHasRemote() { return bHasRemote; }

	void ResetPowerUp(EPowerUpType PowerUpType);

	void OnDeath();
};
