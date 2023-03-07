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
		int TimerCount = 300;
	void BeginPlay() override;

private:
	void ResetLevel();
	FTimerHandle CountDownTimerHandle = FTimerHandle();

	void CountdownTimer();
};
