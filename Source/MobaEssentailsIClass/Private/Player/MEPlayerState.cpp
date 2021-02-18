	// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MEPlayerState.h"

AMEPlayerState::AMEPlayerState()
{
	AbilityComp = CreateDefaultSubobject<UMEAbilitySystemComponent>("AbilitySystemComp");
	AbilityComp->SetIsReplicated(true);
	AbilityComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//probably too high, this is the value for a character.
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AMEPlayerState::GetAbilitySystemComponent() const
{
	return AbilityComp;
}
