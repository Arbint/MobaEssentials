// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MEAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API UMEAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
};


//NOTES:
/*

	Gameplay Abilities:
		Making the gun the `SourceObject` in the [`GameplayAbilitySpec`](https://github.com/tranek/GASDocumentation#concepts-ga-spec) 
		when granting the ability means you'll have access to the gun that granted the ability inside the ability.
	
	GAS
		If your `ASC` is on your `PlayerState`, then you will need to increase the `NetUpdateFrequency` of your `PlayerState`. It defaults to a very 
		low value on the `PlayerState` and can cause delays or perceived lag before changes to things like `Attributes` and `GameplayTags` 
		happen on the clients. Be sure to enable [`Adaptive Network Update Frequency`]
		(https://docs.unrealengine.com/en-US/Gameplay/Networking/Actors/Properties/index.html#adaptivenetworkupdatefrequency), 
		Fortnite uses it.

	Gameplay Tags:
		It is preferable to use a `GameplayTagContainer` over a `TArray<FGameplayTag>` since the `GameplayTagContainers` add some efficiency
		magic. While tags are standard `FNames`, they can be efficiently packed together in `FGameplayTagContainers` for replication if 
		`Fast Replication` is enabled in the project settings. `Fast Replication` requires that the server and the clients have the same list of 
		`GameplayTags`. This generally shouldn't be a problem so you should enable this option.
		
		Delegate for gameplay tags change
		The `ASC` provides a delegate for when `GameplayTags` are added or removed. It takes in a `EGameplayTagEventType` that can specify only to fire 
		when the `GameplayTag` is added/removed or for any change in the `GameplayTag's` `TagMapCount`.
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGDPlayerState::StunTagChanged);
		The callback function has a parameter for the `GameplayTag` and the new `TagCount`.
		virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	Target Data:
		Starting with 4.24, it is now mandatory to call `UAbilitySystemGlobals::InitGlobalData()` to use [`TargetData`](#concepts-targeting-data). 
		The Sample Project does this in `UEngineSubsystem::Initialize()`. See [`InitGlobalData()`](#concepts-asg-initglobaldata) for more information.
	
	Attribute Set:
		To listen for when an `Attribute` changes to update the UI or other gameplay, use 
		`UAbilitySystemComponent::GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute)`. 
		This function returns a delegate that you can bind to that will be automatically called whenever an `Attribute` changes.
		The delegate provides a `FOnAttributeChangeData` parameter with the `NewValue`, `OldValue`, and `FGameplayEffectModCallbackData`. 
		**Note:** The `FGameplayEffectModCallbackData` will only be set on the server.
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AGDPlayerState::HealthChanged);
		virtual void HealthChanged(const FOnAttributeChangeData& Data);

		**Note:** If playing with multiple clients in PIE, you need to disable `Run Under One Process` in the Editor Preferences otherwise the
		`Derived Attributes` will not update when their independent `Attributes` update on clients other than the first.
*/
