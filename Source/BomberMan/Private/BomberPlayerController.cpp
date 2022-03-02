// Fill out your copyright notice in the Description page of Project Settings.


#include "BomberPlayerController.h"
#include "GameFrameWork/Pawn.h"
#include "Bomb.h"
#include "BomberCaracter.h"

void ABomberPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ABomberPlayerController::MoveVertical(float AxisValue)
{
	Pawn = GetPawn();
	if (Pawn) {
		Pawn->AddMovementInput(FVector::ForwardVector,AxisValue);
	}
}

void ABomberPlayerController::MoveHorizontal(float AxisValue)
{
	Pawn = GetPawn();
	if (Pawn) {
		Pawn->AddMovementInput(FVector::RightVector, AxisValue);
	}
}

void ABomberPlayerController::SpawnBombInput()
{
	Pawn = GetPawn();
	if (Pawn) {
		ABomberCaracter* Player1 = Cast<ABomberCaracter>(Pawn);
		if (Player1) {
			Player1->SpawnBomb();
		}
	}
}

void ABomberPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	int32 Id = GetLocalPlayer()->GetControllerId();
	if (Id == 0) {
		InputComponent->BindAxis("MoveVertical_P1",this,&ABomberPlayerController::MoveVertical);
		InputComponent->BindAxis("MoveHorizontal_P1", this, &ABomberPlayerController::MoveHorizontal);
		InputComponent->BindAction("Bomb_P1", EInputEvent::IE_Pressed, this, &ABomberPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDetonateInput_P1", EInputEvent::IE_Pressed, this, &ABomberPlayerController::RemoteDetonateInput);
	}
	if (Id == 1) {
		InputComponent->BindAxis("MoveVertical_P2", this, &ABomberPlayerController::MoveVertical);
		InputComponent->BindAxis("MoveHorizontal_P2", this, &ABomberPlayerController::MoveHorizontal);
		InputComponent->BindAction("Bomb_P2", EInputEvent::IE_Pressed, this, &ABomberPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDetonateInput_P2", EInputEvent::IE_Pressed, this, &ABomberPlayerController::RemoteDetonateInput);
	}
}

void ABomberPlayerController::RemoteDetonateInput()
{
	Pawn = GetPawn();
	if (Pawn) {
		ABomberCaracter* BomberCharacter = Cast<ABomberCaracter>(Pawn);
		if (BomberCharacter) {
			if (!BomberCharacter->GetBHasRemote()) {
				return;
			}
			else {
				for (int i = 0; i < BomberCharacter->PlacedBombsNum(); i++) {
					if (BomberCharacter->GetPlacedBomb(i)) {
						BomberCharacter->GetPlacedBomb(i)->Detonate();
						i--;
					}
				}
			}
		}
	}
}
