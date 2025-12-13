// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/GameplayPlayerController.h"

void AGameplayPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = false;

    FInputModeGameOnly Mode;
    SetInputMode(Mode);

    SetIgnoreLookInput(false);
    SetIgnoreMoveInput(false);
}