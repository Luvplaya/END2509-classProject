// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Both/ButtonWithTextWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UCodeGameInstance;
UCLASS()
class END2509_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButtonWithTextWidget* Play_Button;

	UPROPERTY(meta = (BindWidget))
	UButtonWithTextWidget* Quit_Button;

	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UCodeGameInstance* GI;

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnQuitClicked();
	
};
