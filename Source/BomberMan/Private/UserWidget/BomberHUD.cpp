// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/BomberHUD.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "BomberManGameMode.h"

bool UBomberHUD::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	RestartButton->OnClicked.AddDynamic(this, &UBomberHUD::OnRestartButtonClicked);
	return true;
}

void UBomberHUD::OnRestartButtonClicked()
{
	Cast<ABomberManGameMode>(UGameplayStatics::GetGameMode(this))->Restart();
}

void UBomberHUD::SetRemainTimer(FText TimerText)
{
	RemainTimer->SetText(TimerText);
}

void UBomberHUD::SetP1Text(int Score)
{
	P1_Text->SetText(FText::AsNumber(Score));
}

void UBomberHUD::SetP2Text(int Score)
{
	P2_Text->SetText(FText::AsNumber(Score));
}

void UBomberHUD::SetWinTitle(FText Text)
{
	WinTitle->SetText(Text);
}

void UBomberHUD::SetMenuBackgroundVisible()
{
	MenuBackground->SetVisibility(ESlateVisibility::Visible);
}

