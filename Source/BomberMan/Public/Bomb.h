// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

class ABlastFX;
UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:

	UPROPERTY(VisibleAnywhere,Category="Component")
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BomberSM;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* Sparks;

	FTimerHandle TimerHandle_Detonate;
	UPROPERTY(EditAnywhere,Category = "Value")
	float DetonateDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Value")
	float RemoteDelay = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Value", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float BlastRange = 1.0f;

	UPROPERTY(EditAnywhere, Category = "FX")
	TSubclassOf<ABlastFX> BlastFX;

	class ABomberCaracter* BomberCharacter;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FVector LineTraceDirection(FVector Direction);

	void SpawnBlast(FVector Direction);
	UPROPERTY(EditAnywhere, Category = Explosion)
	class USoundCue* ExplosionSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBlastRange(float TempBlastRange) { this->BlastRange = TempBlastRange; }

	void Detonate();
};
