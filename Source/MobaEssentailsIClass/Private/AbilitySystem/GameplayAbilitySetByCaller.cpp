// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilitySetByCaller.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"
void UGameplayAbilitySetByCaller::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo,TriggerEventData);
	if (EffectClass)
	{
		FGameplayEffectContextHandle OutContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
		OutContext.AddSourceObject(ActorInfo->AvatarActor.Get());
		FGameplayEffectSpecHandle spec = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, 1, OutContext);
		FGameplayTag TagForSetByCaller = FGameplayTag::RequestGameplayTag(FName("EffectID.setByCaller"));
		spec.Data->SetSetByCallerMagnitude(TagForSetByCaller, 1500);
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
		UE_LOG(LogTemp, Warning, TEXT("Ability Casted"));
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
