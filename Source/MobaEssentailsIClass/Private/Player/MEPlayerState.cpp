	// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MEPlayerState.h"
#include "AbilitySystem/MEAttributeSet.h"
#include "Player/MECharacterBase.h"

AMEPlayerState::AMEPlayerState()
{
	AbilityComp = CreateDefaultSubobject<UMEAbilitySystemComponent>("AbilitySystemComp");
	AbilityComp->SetIsReplicated(true);
	AbilityComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//probably too high, this is the value for a character.
	NetUpdateFrequency = 100.f;
	AttributeSet = CreateDefaultSubobject<UMEAttributeSet>("AttributeSet");
}

void AMEPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (GE_StartValues)
	{
		FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle StartValHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GE_StartValues, 0, EffectContext);
		if (StartValHandle.IsValid())
		{
			GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*StartValHandle.Data.Get(), GetAbilitySystemComponent());
		}
	}
	SetupAttributeUpdateCallbacks();
}

UAbilitySystemComponent* AMEPlayerState::GetAbilitySystemComponent() const
{
	return AbilityComp;
}

void AMEPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	AMECharacterBase* Character = GetPawn<AMECharacterBase>();
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthUpdated: max: %f, current: %f"), AttributeSet->GetMaxHealth(), Data.NewValue)
		Character->OnHealthChanged(Data.NewValue, AttributeSet->GetMaxHealth());
	}
}

void AMEPlayerState::SetupAttributeUpdateCallbacks()
{
	AbilityComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AMEPlayerState::HealthChanged);
}
