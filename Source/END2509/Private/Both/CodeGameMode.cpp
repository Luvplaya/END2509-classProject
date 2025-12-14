// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeGameMode.h"
#include "GameFramework/PlayerController.h"

#include "Code/Actors/BasePlayer.h"         
#include "Code/Actors/Agent.h"              
#include "Both/CodeResultsWidget.h"          
#include "Both/CodeGameInstance.h"           


#include "Code/Actors/BaseCharacter.h"  
#include <Kismet/GameplayStatics.h>


void ACodeGameMode::BeginPlay()
{
    Super::BeginPlay();

    
    if (ResultsWidgetClass)
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        ResultsWidget = CreateWidget<UCodeResultsWidget>(PC, ResultsWidgetClass);
    }

   
    NumberOfEnemies = 0;

    TArray<AActor*> Found;

  
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Found);

    for (AActor* A : Found)
    {
        if (ABasePlayer* P = Cast<ABasePlayer>(A))
        {
           
            P->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);
        }
        else
        {
            NumberOfEnemies++;

           
            A->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
        }
    }
}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
    NumberOfEnemies--;

    if (NumberOfEnemies <= 0)
    {
        HandleWin();
    }
}

void ACodeGameMode::RemovePlayer()
{
    UE_LOG(LogTemp, Warning, TEXT("GameMode RemovePlayer -> HandleLose"));
    HandleLose();
}

void ACodeGameMode::HandleWin()
{
    if (!ResultsWidget) return;
    HidePlayerHUD();
    ResultsWidget->AddToViewport();
    ResultsWidget->SetWin();

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }

    GetWorldTimerManager().SetTimer(WinReturnHandle, this,
        &ACodeGameMode::ReturnToMenu, 2.0f, false);

}

void ACodeGameMode::HandleLose()
{
    if (!ResultsWidget) return;
    HidePlayerHUD();
    ResultsWidget->AddToViewport();
    ResultsWidget->SetLose();

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FInputModeUIOnly Mode;
        Mode.SetWidgetToFocus(ResultsWidget->TakeWidget());
        PC->SetInputMode(Mode);
        PC->bShowMouseCursor = true;
    }
}

void ACodeGameMode::ReturnToMenu()
{
    if (UCodeGameInstance* GI = GetGameInstance<UCodeGameInstance>())
    {
        GI->LoadMainMenu();
    }
}
void ACodeGameMode::HidePlayerHUD()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (ABasePlayer* Player = Cast<ABasePlayer>(PC->GetPawn()))
        {
            Player->RemoveHUD();
        }
    }
}
