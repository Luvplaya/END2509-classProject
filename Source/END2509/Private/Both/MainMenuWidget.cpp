// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/MainMenuWidget.h"
#include "Both/CodeGameInstance.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GI = GetGameInstance<UCodeGameInstance>();
	if (!GI) return;

	if (Play_Button)
	{
		Play_Button->OnClickedExposed.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}
	if (Quit_Button)
	{
		Quit_Button->OnClickedExposed.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	if (GI) GI->LoadFirstLevel();
}

void UMainMenuWidget::OnQuitClicked()
{
	if (GI) GI->QuitGame();
}