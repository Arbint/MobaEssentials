// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainInGameUI.h"
#include "UI/ValueMonitor.h"
void UMainInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainInGameUI::UpdateHealthBar(float percent)
{
	HealthBar->SetValue(percent);
}
