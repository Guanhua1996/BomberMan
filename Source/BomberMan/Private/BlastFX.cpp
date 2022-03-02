// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastFX.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
ABlastFX::ABlastFX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	BlastFXSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlastFXSM"));
	BlastFXSM->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABlastFX::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ABlastFX::DelayDestroy, 1.0f, false);
}

void ABlastFX::DelayDestroy()
{
	Destroy();
}

// Called every frame
void ABlastFX::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlastFX::SetupBlast(FVector StartPos, FVector EndPos)
{
	SetActorLocation(FMath::Lerp(StartPos, EndPos, 0.5f));//Lerp 进度插值 起点，终点，百分比 

	float Streth = FVector::Distance(StartPos, EndPos)/100; //Streth 拉伸 起始位置到终止位置的长度

	FVector Scale = GetActorScale3D();

	
	Scale.X = Streth;

	SetActorScale3D(Scale);
}

