// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BomberCaracter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(RootComponent);

	//增加移速
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpeedIcon(TEXT("UTexture2D'/Game/_Project/Textures/SpeedIcon.SpeedIcon'"));
	Sprites.Add(SpeedIcon.Object);

	//增加炸弹上限
	static ConstructorHelpers::FObjectFinder<UTexture2D> BombIcon(TEXT("UTexture2D'/Game/_Project/Textures/BombIcon.BombIcon'"));
	Sprites.Add(BombIcon.Object);

	//增加爆炸范围
	static ConstructorHelpers::FObjectFinder<UTexture2D> LongerBlastsIcon(TEXT("UTexture2D'/Game/_Project/Textures/LongerBlastsIcon.LongerBlastsIcon'"));
	Sprites.Add(LongerBlastsIcon.Object);

	//遥控炸弹
	static ConstructorHelpers::FObjectFinder<UTexture2D> RemoteIcon(TEXT("UTexture2D'/Game/_Project/Textures/RemoteIcon.RemoteIcon'"));
	Sprites.Add(RemoteIcon.Object);



	Billboard->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	int TempRand = FMath::RandRange(0, 3);
	PowerUpType = static_cast<EPowerUpType>(TempRand);
	Billboard->SetSprite(Sprites[TempRand]);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	BomberCharacter = Cast<ABomberCaracter>(OtherActor);
	if (BomberCharacter) {
		switch (PowerUpType) {
		case EPowerUpType::SpeedBoost:
			BomberCharacter->GetCharacterMovement()->MaxWalkSpeed += SpeedBoost;
			break;
		case EPowerUpType::MoreBombs:
			BomberCharacter->IncreaseBombLimit(BombLimitBoost);
			break;
		case EPowerUpType::LongerBlast:
			BomberCharacter->IncreaseBlastRange(BlastRangeBoost);
			break;
		case EPowerUpType::RemoteBomb:
			BomberCharacter->SetBHasRemoteTrue();
			break;
		default:
			break;
		}

		
		
		DelayDestroy();
	}

}

void APowerUp::ResetPlayer()
{
	BomberCharacter->ResetPowerUp(PowerUpType);
	BomberCharacter = nullptr;
	Destroy();
}

void APowerUp::DelayDestroy()
{
	this->SetActorHiddenInGame(true);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &APowerUp::ResetPlayer, 10.0f, false);
}

