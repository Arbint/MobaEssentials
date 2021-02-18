// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MEEngineSubsystem.h"
#include "AbilitySystemGlobals.h"

void UMEEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Ability System Global Data Initialized"));
}
