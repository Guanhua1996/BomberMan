// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BomberManGameMode.h"
#include "PowerUp.generated.h"


UCLASS()
class BOMBERMAN_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBillboardComponent* Billboard;		//存放贴图 可以让贴图一直保持面向摄像头
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TArray<UTexture2D*> Sprites;

	EPowerUpType PowerUpType;
	UPROPERTY(EditAnywhere, Category = "PowerUp")
	int SpeedBoost = 100;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float BlastRangeBoost = 1;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	int BombLimitBoost = 1;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ABomberCaracter* BomberCharacter;

	FTimerHandle TimerHandle_ResetPlayer;

	FTimerHandle TimerHandle_Destroy;

	void ResetPlayer();

	void DelayDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
};
