// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGenerator.h"
#include "Engine/World.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABlockGenerator::ABlockGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = WITH_EDITOR;

	static ConstructorHelpers::FClassFinder<AUnbreakableBlock> UB(TEXT("/Game/Blueprints/BP_UnbreakableBlock"));
	UnbreakableBlock = UB.Class;

	static ConstructorHelpers::FClassFinder<ABreakableBlock> BB(TEXT("/Game/Blueprints/BP_BreakableBlock"));
	BreakableBlock = BB.Class;

	//вСио╫г
	IgnoredPos.Add(FVector(700, -700, 0));
	IgnoredPos.Add(FVector(700, -600, 0)); 
	IgnoredPos.Add(FVector(600, -700, 0));
	//сроб╫г
	IgnoredPos.Add(FVector(-700, 700, 0));
	IgnoredPos.Add(FVector(-700, 600, 0));
	IgnoredPos.Add(FVector(-600, 700, 0));
	//вСоб╫г
	IgnoredPos.Add(FVector(-700, -700, 0));
	IgnoredPos.Add(FVector(-700, -600, 0));
	IgnoredPos.Add(FVector(-600, -700, 0));
	//срио╫г
	IgnoredPos.Add(FVector(700, 700, 0));
	IgnoredPos.Add(FVector(700, 600, 0));
	IgnoredPos.Add(FVector(600, 700, 0));
}

// Called when the game starts or when spawned
void ABlockGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnUnbreakableBlock();
	FindValidPosition();
	bDrawDebugPoint = false;
	SpawnBreakableBlock();
}

void ABlockGenerator::SpawnUnbreakableBlock()
{
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			if(x % 2 != 0 && y % 2 != 0) {
				FVector TempPos = FVector(x-7, y-7, 0) * Scale;
				GetWorld()->SpawnActor<AUnbreakableBlock>(UnbreakableBlock, TempPos,FRotator::ZeroRotator);
			}

		}
	}
}

bool ABlockGenerator::AllowedSpawnPosition(FVector Position)
{
	if (IgnoredPos.Contains(Position)) return false;
	return true;
}

void ABlockGenerator::FindValidPosition()
{
	if (SpawnPos.Num() > 0) SpawnPos.Empty();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			if (x % 2 == 0 || y % 2 == 0) {
				FVector TempPos = FVector(x-7, y-7, 0) * Scale;
				if (AllowedSpawnPosition(TempPos)) {
					SpawnPos.Add(TempPos);
				}
			}
		}
	}
}

void ABlockGenerator::DrawDebugPoint(FVector& Center, const FLinearColor& Color)
{
	UKismetSystemLibrary::DrawDebugPoint(this, Center, 20.0f, Color);
}

void ABlockGenerator::SpawnBreakableBlock()
{
	if (BreakableBlock) {
		int BlocksToSpawn = GetValidPositionCount() * BlockIntensity;
		TArray<FVector> TempPos;
		TempPos.Append(SpawnPos);
		int Index;
		for (int i = 0; i < BlocksToSpawn; i++) {
			Index = FMath::RandRange(0, TempPos.Num() - 1);
			GetWorld()->SpawnActor<ABreakableBlock>(BreakableBlock, TempPos[Index], FRotator::ZeroRotator);
			TempPos.RemoveAt(Index);
		}
	}
}

int ABlockGenerator::GetValidPositionCount()
{
	return SpawnPos.Num();
}

// Called every frame
void ABlockGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bDrawDebugPoint) {
		
		for (auto& Point : SpawnPos) {
			DrawDebugPoint(Point, ValidColor);
		}
		for (auto& Point : IgnoredPos) {
			DrawDebugPoint(Point, InValidColor);
		}
	}
	
}

bool ABlockGenerator::ShouldTickIfViewportsOnly() const
{

	return WITH_EDITOR;
}

