// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableBlock.generated.h"

UCLASS()
class BOMBERMAN_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();

protected:

	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UStaticMeshComponent* BreakableBlockSM;
	
	UPROPERTY(EditAnywhere, Category = "Explosion")
	class UParticleSystem* Explosion;

	class ABomberManGameMode* BomberManGameMode;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	TSubclassOf<class APowerUp> PowerUp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnDestroy();

};
