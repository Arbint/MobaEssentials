// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystem/MEAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
private:
	UMEAbilitySystemComponent* AbilityComp;
};
