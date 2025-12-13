// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class END2509_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

   
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
    TArray<FName> GameLevels;

   
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
    int32 FirstLevelIndex = 1;

    UPROPERTY(EditDefaultsOnly, Category = "Levels")
    int32 CurrentLevelIndex = 1;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void LoadFirstLevel();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void QuitGame();

    UFUNCTION(BlueprintCallable)
    void LoadCurrentLevel();

    UFUNCTION(BlueprintCallable)
    void LoadMainMenu();
    UFUNCTION(BlueprintCallable)
    void LoadLevelSafe(int32 LevelIndex);
};
