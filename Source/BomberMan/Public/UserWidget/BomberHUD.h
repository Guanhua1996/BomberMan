// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BomberHUD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBomberHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* RemainTimer;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* P1_Text;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* P2_Text;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* WinTitle;
	UPROPERTY(Meta = (BindWidget))
		class UButton* RestartButton;
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* MenuBackground;

	virtual bool Initialize() override;

	UFUNCTION()
		void OnRestartButtonClicked();


public:
	void SetRemainTimer(FText TimerText);

	void SetP1Text(int Score);

	void SetP2Text(int Score);

	void SetWinTitle(FText Text);

	void SetMenuBackgroundVisible();
	

};
