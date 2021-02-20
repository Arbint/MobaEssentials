// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AsyncTaskEffectStackChanged.h"

UAsyncTaskEffectStackChanged* UAsyncTaskEffectStackChanged::ListenForGameplayEffectStackChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag EffectGameplayTag)
{
	UAsyncTaskEffectStackChanged* Listener = NewObject<UAsyncTaskEffectStackChanged>();
	Listener->ASC = AbilitySystemComponent;
	Listener->EffectGameplayTag = EffectGameplayTag;

	if (!IsValid(AbilitySystemComponent) || !EffectGameplayTag.IsValid())
	{
		Listener->EndTask();
		return nullptr;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Start listening"))

	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(Listener, &UAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback);
	AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(Listener, &UAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback);

	return Listener;
}

void UAsyncTaskEffectStackChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		ASC->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	}
	UE_LOG(LogTemp, Warning, TEXT("Task Ended"))

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);
	
	if (AssetTags.HasTagExact(EffectGameplayTag)||GrantedTags.HasTagExact(EffectGameplayTag))
	{
		ASC->OnGameplayEffectStackChangeDelegate(ActiveHandle)->AddUObject(this, &UAsyncTaskEffectStackChanged::GameplayEffectStackChanged);
		OnGameplayEffectStackChanged.Broadcast(EffectGameplayTag, ActiveHandle, 1, 0);
	}
}

void UAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved)
{
	FGameplayTagContainer AssetTags;
	EffectRemoved.Spec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	EffectRemoved.Spec.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(EffectGameplayTag) || GrantedTags.HasTagExact(EffectGameplayTag))
	{
		OnGameplayEffectStackChanged.Broadcast(EffectGameplayTag, EffectRemoved.Handle, 0, 1);
	}
}

void UAsyncTaskEffectStackChanged::GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount)
{
	OnGameplayEffectStackChanged.Broadcast(EffectGameplayTag, EffectHandle, NewStackCount, PreviousStackCount);
}
