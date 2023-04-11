// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Gacha1_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GACHA1_API AGacha1_GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AGacha1_GameMode();
	void RestartGameplay(bool Won);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TimerCount = 10;

	void BeginPlay() override;
	void ShowDeathScreen();
	void HideDeathScreen();
	
	void OnDeathScreenDelayExpire();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Death Screen")
		TSubclassOf<UUserWidget> DeathScreenWidgetClass;
	UPROPERTY()
		UUserWidget* DeathScreenWidget;
	UPROPERTY(EditAnywhere, Category = "Death Screen")
		float Delay;
	FTimerHandle DeathScreenDelayHandle;
	void ResetLevel();
	
	
	FTimerHandle CountDownTimerHandle = FTimerHandle();

	void CountdownTimer();
};
