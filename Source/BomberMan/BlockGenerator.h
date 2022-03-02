// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockGenerator.generated.h"

class AUnbreakableBlock;
class ABreakableBlock;
UCLASS()
class BOMBERMAN_API ABlockGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere,Category = "Block Generation")
	TSubclassOf<AUnbreakableBlock> UnbreakableBlock;

	UPROPERTY(EditAnyWhere, Category = "Block Generation")
	TSubclassOf<ABreakableBlock> BreakableBlock;

	UPROPERTY(EditAnyWhere, Category = "Block Generation|Setting")
	int Height = 15, Width = 15;
	UPROPERTY(EditAnyWhere, Category = "Block Generation|Setting")
	float Scale = 100.0f;
	UPROPERTY(EditAnyWhere, Category = "Block Generation", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BlockIntensity = 0.7f;

	UPROPERTY(VisibleAnyWhere, Category = "Block Generation|Setting")
	TArray<FVector> SpawnPos;	//备选位置
	UPROPERTY(EditAnyWhere, Category = "Block Generation|Setting")
	TArray<FVector> IgnoredPos;		//忽略位置

	const FLinearColor ValidColor = FLinearColor(0, 0, 0.8f);
	const FLinearColor InValidColor = FLinearColor(0.8f, 0, 0.0f);

	UPROPERTY(EditAnyWhere, Category = "Block Generation|Debug")
	bool bDrawDebugPoint = true;

	void SpawnUnbreakableBlock();
	bool AllowedSpawnPosition(FVector Position);

	UFUNCTION(BlueprintCallable)
	void FindValidPosition();
	void DrawDebugPoint(FVector& Center, const FLinearColor& Color);
	void SpawnBreakableBlock();
	int GetValidPositionCount();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;
};
