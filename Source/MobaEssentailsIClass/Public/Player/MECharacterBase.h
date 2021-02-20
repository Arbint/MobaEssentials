// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MECharacterBase.generated.h"

UCLASS()
class MOBAESSENTAILSICLASS_API AMECharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMECharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void OnHealthChanged(float newHealth, float MaxHealth);
	
	virtual void PossessedBy(AController* NewController) override;
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	class UMEAbilitySystemComponent* GetASC() {return AbilityComp; }

	virtual void OnRep_PlayerState() override;
	private:
	/*
	Initialize the ability system component lived on the player state.
		-	called by PossessedBy() so the server does the initialization
		-	called by OnRep_PlayerState() so the client initializes it
	*/
	void InitAbilitySystemCompFromState();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	TMap<FName, int> GetGamePlayTagInfo();

	UPROPERTY()
	class UMEAbilitySystemComponent* AbilityComp;

};
