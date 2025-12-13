// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/MenuPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (MenuClass)
	{
		MenuInstance = CreateWidget<UUserWidget>(this, MenuClass);
		if (MenuInstance)
		{
			MenuInstance->AddToViewport();

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(MenuInstance->TakeWidget());
			Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			SetInputMode(Mode);
		}
	}
}
