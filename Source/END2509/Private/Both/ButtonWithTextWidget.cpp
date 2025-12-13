// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/ButtonWithTextWidget.h"

void UButtonWithTextWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (Information)
	{
		Information->SetText(InfoText); 
	}
}

void UButtonWithTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundButton)
	{
		BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithTextWidget::HandleInternalClick);
	}
}

void UButtonWithTextWidget::HandleInternalClick()
{
	OnClickedExposed.Broadcast();
}