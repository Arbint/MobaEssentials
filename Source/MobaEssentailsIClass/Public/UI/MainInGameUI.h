// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainInGameUI.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API UMainInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
    UPROPERTY(meta = (BindWidget))
    class UValueMonitor* HealthBar;
    UPROPERTY(meta = (BindWidget))
    class UValueMonitor* ManaBar;
    
    UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealthBar(float percent);
};
