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

	void RestartGameplay(bool Won);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TimerCount = 10;

	void BeginPlay() override;
	void ShowDeathScreen();
	void HideDeathScreen();
	
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Death Screen")
		TSubclassOf<UUserWidget> DeathScreenWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death Screen")
		float DeathScreenDelayTime = 3.0f;
	UPROPERTY()
		UUserWidget* DeathScreenWidget;
	FTimerHandle DeathScreenDelayHandle;
private:
	void ResetLevel();
	
	void OnDeathScreenDelayExpire();
	FTimerHandle CountDownTimerHandle = FTimerHandle();

	void CountdownTimer();
};
