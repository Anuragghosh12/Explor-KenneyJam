// Fill out your copyright notice in the Description page of Project Settings.


#include "Gacha1_GameMode.h"
#include "Kismet/GameplayStatics.h"


void AGacha1_GameMode::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&AGacha1_GameMode::CountdownTimer, 1.0f, true, 1.0f);
}
void AGacha1_GameMode::RestartGameplay(bool Won)
{
	if (Won)
	{
		ResetLevel();
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGacha1_GameMode::ResetLevel, 5.0f);
	}
}
void AGacha1_GameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TestingGrounds");
}

void AGacha1_GameMode::CountdownTimer()
{
	TimerCount--;
	if (TimerCount <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		ResetLevel();
	}
}