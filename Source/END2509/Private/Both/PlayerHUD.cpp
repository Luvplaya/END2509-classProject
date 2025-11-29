// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/SlateBlueprintLibrary.h"      
#include "Kismet/GameplayStatics.h"               
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void UPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct(); 
    
    if (Crosshair && CrosshairMaterial)
    {
        CrosshairMID = UMaterialInstanceDynamic::Create(CrosshairMaterial, this);
        Crosshair->SetBrushFromMaterial(CrosshairMID);
        SetCrosshairColor(SafeColor);
    }
    SetHealth(1.f);
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeo, float InDeltaTime)
{
    Super::NativeTick(MyGeo, InDeltaTime);
    UpdateCrosshairAndTrace(MyGeo);
}

void UPlayerHUD::SetHealth(float Percent)
{
    if (HealthBar)
    {
        UE_LOG(LogTemp, Warning, TEXT("[HUD] SetHealth %.2f"), Percent);
        HealthBar->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
    }
}

void UPlayerHUD::SetCrosshairColor(const FLinearColor& Color)
{
    if (CrosshairMID) CrosshairMID->SetVectorParameterValue(ColorParamName, Color);

}

void UPlayerHUD::UpdateCrosshairAndTrace(const FGeometry& Geo)
{
    if (!Crosshair) return;

   
    FVector2D PixelPos, ViewportPos;
    const FVector2D Half = Geo.GetLocalSize() * 0.5f;
    USlateBlueprintLibrary::LocalToViewport(this, Geo, Half, PixelPos, ViewportPos);

   
    APlayerController* PC = GetOwningPlayer();
    if (!PC) return;

    FVector WorldPos, WorldDir;
    UGameplayStatics::DeprojectScreenToWorld(PC, PixelPos, WorldPos, WorldDir);

    const float Dist = 100000.0f;
    const FVector RayEnd = WorldPos + WorldDir * Dist;

    
    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(ECC_Pawn);
    Obj.AddObjectTypesToQuery(ECC_WorldDynamic);
    Obj.AddObjectTypesToQuery(ECC_WorldStatic);
    FCollisionQueryParams Params(SCENE_QUERY_STAT(HUDTrace), true);
    if (APawn* OwnerPawn = GetOwningPlayerPawn()) 
    {
        Params.AddIgnoredActor(OwnerPawn); 
    }
    FHitResult Hit;
    const bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, WorldPos, RayEnd, Obj, Params);

    if (bHit)
    {
        Endpoint = Hit.ImpactPoint;

        bool bHitPawn = false;
        if (UPrimitiveComponent* C = Hit.Component.Get())
            bHitPawn = (C->GetCollisionObjectType() == ECC_Pawn);
       
        SetCrosshairColor(bHitPawn ? DangerColor : SafeColor);

        
    }
    else
    {
        Endpoint = RayEnd;
        SetCrosshairColor(SafeColor);
    }
}
