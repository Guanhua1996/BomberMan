// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "LocalMPGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ULocalMPGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

		virtual bool InputKey
		(
			const FInputKeyEventArgs& EventArgs

		)override;

		/*virtual bool InputKey
		(
			FViewport* Viewport,
			int32 ControllerId,
			FKey Key,
			EInputEvent Event,
			float AmountDepressed,
			bool bGamepad
		) override;*/
		
	virtual bool InputAxis
	(
		FViewport* Viewport1,
		int32 ControllerId,
		FKey Key,
		float Delta,
		float DeltaTime,
		int32 NumSamples,
		bool bGamepad
	) override;
	
	
};
