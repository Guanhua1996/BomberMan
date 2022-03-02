// Fill out your copyright notice in the Description page of Project Settings.


#include "BomberCaracter.h"
#include "UObject/ConstructorHelpers.h"
#include "Bomb.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BomberManGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABomberCaracter::ABomberCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<ABomb> TempBomb(TEXT("/Game/Blueprints/BP_Bomb"));
	Bomb = TempBomb.Class;
}

// Called when the game starts or when spawned
void ABomberCaracter::BeginPlay()
{
	Super::BeginPlay();

	BombLimit = InitialBombLimit;
	BlastRange = InitialBlastRange;
	GetCharacterMovement()->MaxWalkSpeed = InitialMaxWalkSpeed;
	GameMode = Cast<ABomberManGameMode>(UGameplayStatics::GetGameMode(this));
}

float ABomberCaracter::GetSnappedValue(int Value, float Scale)
{
	int Remains = Value % (int)Scale;
	return FMath::Abs(Remains) > Scale / 2 ? Value - Remains + (Value > 0 ? Scale : -Scale) : Value - Remains;
}

FVector ABomberCaracter::GetSnappedPosition(FVector SourcePos)
{
	SourcePos.X = GetSnappedValue(SourcePos.X, 100.0f);
	SourcePos.Y = GetSnappedValue(SourcePos.Y, 100.0f);
	FVector TempPos = FVector(SourcePos.X, SourcePos.Y, 0);
	return TempPos;
}


// Called every frame
void ABomberCaracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABomberCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ABomberCaracter::SpawnBomb()
{
	if (PlacedBombs.Num() >= BombLimit) {
		return;
	}

	if (Bomb) {
		FActorSpawnParameters Params;
		Params.Owner = this;
		FVector TempLocation = GetSnappedPosition(GetActorLocation());
		ABomb* TempBomb = GetWorld()->SpawnActor<ABomb>(Bomb, TempLocation, FRotator::ZeroRotator,Params);
		TempBomb->SetBlastRange(BlastRange);
		PlacedBombs.Add(TempBomb);
	}
}

void ABomberCaracter::ResetPowerUp(EPowerUpType PowerUpType)
{
	switch (PowerUpType) {
	case EPowerUpType::SpeedBoost:
		GetCharacterMovement()->MaxWalkSpeed -= SpeedReduce;
		break;
	case EPowerUpType::MoreBombs:
		BombLimit -= BombLimitReduce;
		break;
	case EPowerUpType::LongerBlast:
		BlastRange -= BlastRangeReduce;
		break;
	case EPowerUpType::RemoteBomb:
		bHasRemote = false;
		break;
	default:
		break;
	}
	
}

void ABomberCaracter::OnDeath()
{
	if (!bHasDead) {
		bHasDead = true;
		GameMode->OnPlayerDeath(GetController());
	}
	
}

