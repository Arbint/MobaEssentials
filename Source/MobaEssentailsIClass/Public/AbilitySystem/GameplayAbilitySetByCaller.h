// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySetByCaller.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API UGameplayAbilitySetByCaller : public UGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SetByCaller")
	TSubclassOf<UGameplayEffect> EffectClass;
};
