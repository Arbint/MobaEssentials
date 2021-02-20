// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MEPlayerController.h"
#include "UI/MainInGameUI.h"

AMEPlayerController::AMEPlayerController()
{
	bReplicates = true;	
}

void AMEPlayerController::OnHealthChanged(float newHealth, float MaxHealth)
{
	if (MainUI)
	{
		MainUI->UpdateHealthBar(newHealth/MaxHealth);
	}
}

void AMEPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CreateUI();

}

void AMEPlayerController::CreateUI()
{
	if (MainInGameUIClass && IsLocalController())
	{
		MainUI = CreateWidget<UMainInGameUI>(this, MainInGameUIClass);
		if (MainUI)
		{
			MainUI->AddToViewport();
		}
	}
}
