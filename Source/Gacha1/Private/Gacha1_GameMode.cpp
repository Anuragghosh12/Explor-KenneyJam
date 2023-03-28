// Fill out your copyright notice in the Description page of Project Settings.


#include "Gacha1_GameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void AGacha1_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if(DeathScreenWidgetClass!=nullptr)
	{
		DeathScreenWidget = CreateWidget<UUserWidget>(GetWorld(), DeathScreenWidgetClass);
		if (DeathScreenWidget!=nullptr)
		{
			DeathScreenWidget->AddToViewport();
			DeathScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&AGacha1_GameMode::CountdownTimer, 1.0f, true, 1.0f);
}

void AGacha1_GameMode::ShowDeathScreen()
{
	if(DeathScreenWidget!=nullptr)
	{
		
			DeathScreenWidget->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetTimerManager().SetTimer(DeathScreenDelayHandle, this, &AGacha1_GameMode::OnDeathScreenDelayExpire, 3.0f);
		
	}
}

void AGacha1_GameMode::HideDeathScreen()
{
	if(DeathScreenWidget!=nullptr)
	{
		DeathScreenWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGacha1_GameMode::OnDeathScreenDelayExpire()
{
	HideDeathScreen();
	RestartGameplay(true);
}

void AGacha1_GameMode::RestartGameplay(bool Won)
{
	if (Won)
	{
		AGacha1_GameMode* ThisGameMode = Cast<AGacha1_GameMode>(GetWorld()->GetAuthGameMode());
		if(ThisGameMode)
		{
			ThisGameMode->ShowDeathScreen();
		}
		
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
