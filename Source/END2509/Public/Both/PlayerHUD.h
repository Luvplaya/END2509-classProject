// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
class UProgressBar;
class UImage;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UTextBlock;
UCLASS(BlueprintType, Blueprintable)
class END2509_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly,meta =(BindWidget))
	class UProgressBar* HealthBar;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeo, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget)) UImage* Crosshair = nullptr;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "HUD") UMaterialInterface* CrosshairMaterial = nullptr;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "HUD") FName ColorParamName = TEXT("Color");
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "HUD") FLinearColor SafeColor = FLinearColor(0.1f, 0.1f, 0.7f, 1.f);
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "HUD") FLinearColor DangerColor = FLinearColor(0.85f, 0.1f, 0.1f, 1.f);

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* CurrentAmmo;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* MaxAmmo;
public:
	
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Percent);
	
	UFUNCTION(BlueprintPure , Category = "HUD")
	FVector GetDestination() const { return Endpoint; }
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetCrosshairColor(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetAmmo(float Current, float Max);
private:
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* CrosshairMID = nullptr;
	FVector Endpoint = FVector::ZeroVector;
	
	
	void UpdateCrosshairAndTrace(const FGeometry& Geo);
};
