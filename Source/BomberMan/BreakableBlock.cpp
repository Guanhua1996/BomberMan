// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "BomberManGameMode.h"
#include "Engine/World.h"
#include "PowerUp.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BreakableBlockSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreakableBlockSM"));
	RootComponent = BreakableBlockSM;

	static ConstructorHelpers::FClassFinder<APowerUp> Pu(TEXT("/Game/Blueprints/BP_PowerUp"));
	PowerUp = Pu.Class;


}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	BomberManGameMode = Cast<ABomberManGameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableBlock::OnDestroy()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation(), GetActorRotation()); //World ParticleSystem Location Rotation

	if (FMath::RandRange(0.0f, 1.0f) < BomberManGameMode->GetDropChance()) {
		GetWorld()->SpawnActor<APowerUp>(PowerUp, GetActorLocation(), GetActorRotation());
	}

	Destroy();

}

