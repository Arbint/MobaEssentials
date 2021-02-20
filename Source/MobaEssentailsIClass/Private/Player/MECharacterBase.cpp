// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MECharacterBase.h"
#include "Player/MEPlayerState.h"
#include "Player/MEPlayerController.h"
#include "AbilitySystem/MEAbilitySystemComponent.h"
// Sets default values
AMECharacterBase::AMECharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AMECharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMECharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMECharacterBase::OnHealthChanged(float newHealth, float MaxHealth)
{
	AMEPlayerController* pc = GetController<AMEPlayerController>();
	if (pc)
	{
		pc->OnHealthChanged(newHealth, MaxHealth);
	}
}

void AMECharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemCompFromState();
}

void AMECharacterBase::InitAbilitySystemCompFromState()
{
	AMEPlayerState* playerState = GetPlayerState<AMEPlayerState>();
	if (playerState)
	{
		AbilityComp = Cast<UMEAbilitySystemComponent>(playerState->GetAbilitySystemComponent());
		playerState->GetAbilitySystemComponent()->InitAbilityActorInfo(playerState, this);
	}
}

TMap<FName, int> AMECharacterBase::GetGamePlayTagInfo()
{
	TMap<FName, int> TagCountMap;
	if (AbilityComp)
	{
		FGameplayTagContainer OwningTags;
		AbilityComp->GetOwnedGameplayTags(OwningTags);
	for (FGameplayTag item : OwningTags)
		{
			TagCountMap.Add(item.GetTagName(), AbilityComp->GetTagCount(item));
		}
	}
	return TagCountMap;
}

void AMECharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemCompFromState();
}

