// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "BlastFX.h"
#include "../BreakableBlock.h"
#include "BomberCaracter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BomberSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BomberSM"));
	BomberSM->SetupAttachment(RootComponent);

	Sparks= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Sparks"));
	Sparks->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this,&ABomb::OnOverlapEnd);//EndOverlap,ָ��ײ������ʱ�򴥷�

	BomberCharacter = Cast<ABomberCaracter>(GetOwner());

	if (BomberCharacter->GetBHasRemote()) {
		GetWorldTimerManager().SetTimer(TimerHandle_Detonate, this, &ABomb::Detonate, RemoteDelay, false);
	}
	else {
		GetWorldTimerManager().SetTimer(TimerHandle_Detonate, this, &ABomb::Detonate, DetonateDelay, false);
	}

	
	
}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor==GetOwner()) {
		BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);//������ײΪ����
	}
}

void ABomb::Detonate()
{
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	SpawnBlast(FVector::RightVector);
	SpawnBlast(FVector::ForwardVector);
	if (BomberCharacter)
		BomberCharacter->RemoveBomb(this);
	Destroy();
}

FVector ABomb::LineTraceDirection(FVector Direction)
{
	//�¼���� �Ƿ�����actor
	TArray<FHitResult> Hits;

	FVector Origin = GetActorLocation();

	FVector EndPos = Origin + Direction * 100 * BlastRange;

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceMultiByChannel(Hits, Origin, EndPos, ECollisionChannel::ECC_GameTraceChannel1,Params);

	if (Hits.Num() > 0) {
		EndPos = Hits.Last().ImpactPoint;//��ȡ���һ��ֵ�ĵ�
		for (auto& Hit : Hits) {
			ABreakableBlock* BreakableBlock = Cast<ABreakableBlock>(Hit.GetActor());	//ǿתhit���ÿ��actor��AB����
			if (BreakableBlock) {					//���ת���ɹ�˵���ҵ���
				BreakableBlock->OnDestroy();
			}
			else {
				ABomberCaracter* Player = Cast<ABomberCaracter>(Hit.GetActor());
				if (Player) {
					Player->OnDeath();
				}
			}
		}
	}

	return EndPos;
}

void ABomb::SpawnBlast(FVector Direction)
{
	if (Direction == FVector::ForwardVector) {
		ABlastFX* Blast = GetWorld()->SpawnActor<ABlastFX>(BlastFX, GetActorLocation(), FRotator::ZeroRotator);
		Blast->SetupBlast(LineTraceDirection(Direction), LineTraceDirection(-Direction));
	}
	else if(Direction == FVector::RightVector){
		FRotator Rotator;
		Rotator.Yaw = 90.0f;
		Rotator.Pitch = 0.0f;
		Rotator.Roll = 0.0f;
		ABlastFX* Blast = GetWorld()->SpawnActor<ABlastFX>(BlastFX, GetActorLocation(), Rotator);//����ֱ������Y Ҫ����XȻ����ת
		Blast->SetupBlast(LineTraceDirection(Direction), LineTraceDirection(-Direction));
	}
	
	

}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

