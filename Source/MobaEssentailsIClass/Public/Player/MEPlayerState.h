// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/MEAbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

#include "MEPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API AMEPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AMEPlayerState();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UMEAttributeSet* GetAttributeSet() const {return AttributeSet; }
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Defaults")
	TSubclassOf<UGameplayEffect> GE_StartValues;
private:
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	//should be called after setting the basic values
	virtual void SetupAttributeUpdateCallbacks();
private:

	UMEAbilitySystemComponent* AbilityComp;
	UMEAttributeSet* AttributeSet;
};
