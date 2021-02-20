// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API AMEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMEPlayerController();
	void OnHealthChanged(float newHealth, float MaxHealth);
	virtual void BeginPlay() override;

	void CreateUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UMainInGameUI> MainInGameUIClass;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "UI")
	class UMainInGameUI* MainUI;
};
