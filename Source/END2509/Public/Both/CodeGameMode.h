// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeGameMode.generated.h"

/**
 * 
 */
class UCodeResultsWidget;  
class ABaseCharacter;       
class ABasePlayer;
UCLASS()
class END2509_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rules")
    int32 NumberOfEnemies = 0;

   
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UCodeResultsWidget> ResultsWidgetClass;

    UPROPERTY()
    UCodeResultsWidget* ResultsWidget = nullptr;

    FTimerHandle WinReturnHandle;

   
    UFUNCTION()
    void RemoveEnemy(AActor* DestroyedActor);

    
    UFUNCTION()
    void RemovePlayer();

    void HandleWin();
    void HandleLose();

    void ReturnToMenu();
    void HidePlayerHUD();
    int32 SpawnersAlive = 0;

    UFUNCTION()
    void OnSpawnerDestroyed(AActor* DestroyedActor);

    void CheckWinCondition();
};
