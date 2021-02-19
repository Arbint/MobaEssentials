// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MEAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectAggregatorLibrary.h"

UMEAttributeSet::UMEAttributeSet()
{
	Health.SetBaseValue(200.f);
	MaxHealth.SetBaseValue(200.f);
}

void UMEAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//here we can respaond to changes to a currentvalue before the change happens, it is the idal place to clamp incoming changes to currentValue 
	//via reference parameter new value
	//example:
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
	}
}

void UMEAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//this function only triggered after an instant GameplayEffect changes the base value of an attribute.
}

void UMEAttributeSet::OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute, FAggregator* NewAggregator) const
{
	Super::OnAttributeAggregatorCreated(Attribute, NewAggregator);
	if (!NewAggregator)
	{
		return;
	}
	if (Attribute == GetMoveSpeedAttribute())
	{
		NewAggregator->EvaluationMetaData = &FAggregatorEvaluateMetaDataLibrary::MostNegativeMod_AllPositiveMods;
	}
}

void UMEAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMEAttributeSet, Health, OldHealth);
}

void UMEAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMovepeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMEAttributeSet, MoveSpeed, OldMovepeed);
}

void UMEAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMEAttributeSet, MaxHealth, OldMaxHealth); 
}

void UMEAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMEAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UMEAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UMEAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always)
}
