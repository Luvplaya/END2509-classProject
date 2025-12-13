// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeResultsWidget.generated.h"

/**
 * 
 */
class UWidgetSwitcher;
class UPanelWidget;
class UButtonWithTextWidget;
class UCodeGameInstance;

UCLASS()
class END2509_API UCodeResultsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetWin();

    UFUNCTION(BlueprintCallable)
    void SetLose();

protected:
    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* WidgetSwitcher;

    UPROPERTY(meta = (BindWidget))
    UPanelWidget* ButtonArea;

    UPROPERTY(meta = (BindWidget))
    UButtonWithTextWidget* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UButtonWithTextWidget* MenuButton;

    UPROPERTY()
    UCodeGameInstance* CachedGI;

    UFUNCTION()
    void OnRestartClicked();

    UFUNCTION()
    void OnMenuClicked();
};
