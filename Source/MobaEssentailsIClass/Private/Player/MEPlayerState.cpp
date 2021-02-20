	// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MEPlayerState.h"
#include "AbilitySystem/MEAttributeSet.h"
#include "Player/MECharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	InitDefaultAttributes();
	SetupAttributeUpdateCallbacks();
}

void AMEPlayerState::InitDefaultAttributes()
{
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
		Character->OnHealthChanged(Data.NewValue, AttributeSet->GetMaxHealth());
	}
}

void AMEPlayerState::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	AMECharacterBase* Character = GetPawn<AMECharacterBase>();
	if (Character)
	{
	Character->GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
	}
}

void AMEPlayerState::SetupAttributeUpdateCallbacks()
{
	AbilityComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AMEPlayerState::HealthChanged);
	AbilityComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &AMEPlayerState::MoveSpeedChanged);
}
