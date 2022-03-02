// Fill out your copyright notice in the Description page of Project Settings.


#include "BomberManGameMode.h"
#include "BomberPlayerController.h"
#include "BomberCaracter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetStringLibrary.h"
#include "UserWidget/BomberHUD.h"
#include "Kismet/GameplayStatics.h"
#include "BomberSaveGame.h"
#include "Blueprint/UserWidget.h"

ABomberManGameMode::ABomberManGameMode()
{
	/*
	* 这里应该这样设置,但是由于之前已经写过蓝图类了,所以用另外一种方式
	* DefaultPawnClass = ABomberCaracter::StaticClass();
	*/
	//复制引用的Blueprint, 最后一截名字和'' 要删除!
	static ConstructorHelpers::FClassFinder<ABomberCaracter> BomberCharacter(TEXT("/Game/Blueprints/BP_BomberCharacter"));
	DefaultPawnClass = BomberCharacter.Class;
	PlayerControllerClass = ABomberPlayerController::StaticClass();

	//设置成true才会每帧都调用tick
	PrimaryActorTick.bCanEverTick = true;


}

void ABomberManGameMode::BeginPlay()
{
	Super::BeginPlay();
	BomberHUD = CreateWidget<UBomberHUD>(GetWorld(), LoadClass<UBomberHUD>(this, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_HUD.WBP_HUD_C'")));
	BomberHUD->AddToViewport();
	BomberSaveInstance = Cast<UBomberSaveGame>(UGameplayStatics::CreateSaveGameObject(UBomberSaveGame::StaticClass()));
}

void ABomberManGameMode::IncrementP1Victories()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		BomberSaveInstance =Cast<UBomberSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else {
		BomberSaveInstance = Cast<UBomberSaveGame>(UGameplayStatics::CreateSaveGameObject(UBomberSaveGame::StaticClass()));
	}

	BomberSaveInstance->IncreaseP1Victories();

	UGameplayStatics::SaveGameToSlot(BomberSaveInstance, SaveSlotName, UserIndex);

	
}

void ABomberManGameMode::IncrementP2Victories()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		BomberSaveInstance = Cast<UBomberSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else {
		BomberSaveInstance = Cast<UBomberSaveGame>(UGameplayStatics::CreateSaveGameObject(UBomberSaveGame::StaticClass()));
	}

	BomberSaveInstance->IncreaseP2Victories();

	UGameplayStatics::SaveGameToSlot(BomberSaveInstance, SaveSlotName, UserIndex);
}

void ABomberManGameMode::UpdateScore()
{
	BomberHUD->SetP1Text(BomberSaveInstance->GetP1Victories());
	BomberHUD->SetP2Text(BomberSaveInstance->GetP2Victories());
	BomberHUD->SetMenuBackgroundVisible();
}

void ABomberManGameMode::OnGameEnd()
{
	UGameplayStatics::SetGamePaused(this, true);
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
}

void ABomberManGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TotalTime -= DeltaSeconds;
	TimeText = FText::FromString(UKismetStringLibrary::TimeSecondsToString(TotalTime));
	BomberHUD->SetRemainTimer(TimeText);
}

void ABomberManGameMode::OnPlayerDeath(AController* Controller)
{
	ABomberPlayerController* BomberPlayerController = Cast<ABomberPlayerController>(Controller);
	FText Player1WinText = FText::FromString("Player 1 Win !");
	FText Player2WinText = FText::FromString("Player 2 Win !");

	if (UGameplayStatics::GetPlayerControllerID(BomberPlayerController) == 0) {
		BomberHUD->SetWinTitle(Player2WinText);
		IncrementP2Victories();
	}
	else if (UGameplayStatics::GetPlayerControllerID(BomberPlayerController) == 1) {
		BomberHUD->SetWinTitle(Player1WinText);
		IncrementP1Victories();
	}
	UpdateScore();
	OnGameEnd();
	
}

void ABomberManGameMode::Restart()
{
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(this, 1), Destroy());
	UGameplayStatics::OpenLevel(this, "Level01");
}
