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
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TimerCount = 2.f;
	void BeginPlay() override;
	void ShowDeathScreen();
	void HideDeathScreen();
	void OnDeathScreenDelayExpire();
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* ExplosionEffect;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Death Screen")
		TSubclassOf<UUserWidget> DeathScreenWidgetClass;
	UPROPERTY()
		UUserWidget* DeathScreenWidget;
	UPROPERTY(EditAnywhere, Category = "Death Screen")
		float Delay=3.f;
	FTimerHandle DeathScreenDelayHandle;
	void ResetLevel();

	float Timer, Del;
	
	FTimerHandle CountDownTimerHandle = FTimerHandle();
	FTimerHandle DelayTimerHandle = FTimerHandle();
	void CountdownTimer();
};
