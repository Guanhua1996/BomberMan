// Fill out your copyright notice in the Description page of Project Settings.


#include "UnbreakableBlock.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUnbreakableBlock::AUnbreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnbreakableBlockSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnbreakableBlockSM"));
	RootComponent = UnbreakableBlockSM;
}

// Called when the game starts or when spawned
void AUnbreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnbreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

