// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeResultsWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/PanelWidget.h"
#include "Both/ButtonWithTextWidget.h"
#include "Both/CodeGameInstance.h" 


void UCodeResultsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    CachedGI = GetGameInstance<UCodeGameInstance>();

    if (RestartButton)
        RestartButton->OnClickedExposed.AddDynamic(this, &UCodeResultsWidget::OnRestartClicked);

    if (MenuButton)
        MenuButton->OnClickedExposed.AddDynamic(this, &UCodeResultsWidget::OnMenuClicked);
}

void UCodeResultsWidget::OnRestartClicked()
{
    if (CachedGI) CachedGI->LoadCurrentLevel();
}

void UCodeResultsWidget::OnMenuClicked()
{
    if (CachedGI) CachedGI->LoadMainMenu();
}

void UCodeResultsWidget::SetWin()
{
    if (WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(1); 
    if (ButtonArea) ButtonArea->SetVisibility(ESlateVisibility::Collapsed);
}

void UCodeResultsWidget::SetLose()
{
    if (WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(0); 
    if (ButtonArea) ButtonArea->SetVisibility(ESlateVisibility::Visible);
}