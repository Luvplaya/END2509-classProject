// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeGameMode.h"
#include "GameFramework/PlayerController.h"

#include "Code/Actors/BasePlayer.h"         
#include "Code/Actors/Agent.h"              
#include "Both/CodeResultsWidget.h"          
#include "Both/CodeGameInstance.h"           


#include "Code/Actors/BaseCharacter.h"  
#include "EngineUtils.h" 
#include <Both/Spawner.h>


void ACodeGameMode::BeginPlay()
{
    Super::BeginPlay();

    
    if (ResultsWidgetClass)
    {
        if (APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr)
        {
            ResultsWidget = CreateWidget<UCodeResultsWidget>(PC, ResultsWidgetClass);
        }
    }

   
    NumberOfEnemies = 0;

    for (TActorIterator<ABaseCharacter> It(GetWorld()); It; ++It)
    {
        ABaseCharacter* Char = *It;
        if (!Char) continue;

       
        if (ABasePlayer* P = Cast<ABasePlayer>(Char))
        {
           
            P->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);
            continue;
        }

      
        if (AAgent* Enemy = Cast<AAgent>(Char))
        {
            NumberOfEnemies++;
            Enemy->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
        }
    }
    SpawnersAlive = 0;
    for (TActorIterator<ASpawner> It(GetWorld()); It; ++It)
    {
        ASpawner* S = *It;
        if (!S) continue;

        SpawnersAlive++;
        S->OnDestroyed.AddDynamic(this, &ACodeGameMode::OnSpawnerDestroyed);
    }

}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
    NumberOfEnemies--;

    CheckWinCondition();
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

    if (APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr)
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

    if (APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr)
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
    if (APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr)
    {
        if (ABasePlayer* Player = Cast<ABasePlayer>(PC->GetPawn()))
        {
            Player->RemoveHUD();
        }
    }
}
void ACodeGameMode::OnSpawnerDestroyed(AActor* DestroyedActor)
{
    SpawnersAlive--;
    CheckWinCondition();
}

void ACodeGameMode::CheckWinCondition()
{
    if (NumberOfEnemies <= 0 && SpawnersAlive <= 0)
    {
        HandleWin();
    }
}