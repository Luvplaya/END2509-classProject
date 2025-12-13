// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeGameInstance.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"



void UCodeGameInstance::LoadFirstLevel()
{
    if (!GameLevels.IsValidIndex(FirstLevelIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid FirstLevelIndex %d"), FirstLevelIndex);
        return;
    }

    if (UWorld* World = GetWorld())
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            const FString LevelName = GameLevels[FirstLevelIndex].ToString();
            PC->ClientTravel(LevelName, ETravelType::TRAVEL_Absolute);
        }
    }
}

void UCodeGameInstance::QuitGame()
{
    //UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
    if (UWorld* World = GetWorld())
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, false);
        }
    }
}