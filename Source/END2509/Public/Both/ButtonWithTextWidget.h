// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWithTextWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonWithTextClicked); 
UCLASS()
class END2509_API UButtonWithTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "ButtonWithText")
	FOnButtonWithTextClicked OnClickedExposed;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonWithText", meta = (ExposeOnSpawn = true))
	FText InfoText = FText::FromString(TEXT("Default"));

protected:
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Information;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void HandleInternalClick();
};
