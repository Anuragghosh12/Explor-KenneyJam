// Fill out your copyright notice in the Description page of Project Settings.


#include "Gacha1_GameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Main2.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



AGacha1_GameMode::AGacha1_GameMode()
{
	
	
	static ConstructorHelpers::FClassFinder<UUserWidget> DeathScreenWidgetClassFinder(TEXT("/Game/Widget/Death_Screen"));
	if (DeathScreenWidgetClassFinder.Succeeded())
	{
		DeathScreenWidgetClass = DeathScreenWidgetClassFinder.Class;
	}
}
void AGacha1_GameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&AGacha1_GameMode::CountdownTimer, 1.0f, true, 1.0f);
	Del = Delay;
	HideDeathScreen();
}

void AGacha1_GameMode::ShowDeathScreen()
{
	DeathScreenWidget = CreateWidget<UUserWidget>(GetWorld(), DeathScreenWidgetClass);

	// Add the widget to the viewport
	
	if(DeathScreenWidget && !DeathScreenWidget->IsInViewport())
	{
		DeathScreenWidget->AddToViewport();
	}
}

void AGacha1_GameMode::HideDeathScreen()
{
	if (DeathScreenWidget)
	{
		DeathScreenWidget->RemoveFromParent();
		DeathScreenWidget = nullptr;
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
		ResetLevel();
	}
	else
	{
		
		ResetLevel();
	}
}

void AGacha1_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TimerCount <= 0)
	{
		
		Del-=DeltaTime;
		if (Del <= 0)
		{
			OnDeathScreenDelayExpire();
		}
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
		ShowDeathScreen();
		if (Del <= 0)
		{
			GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
			RestartGameplay(true);
			Del = Delay;
		}
	}
}
