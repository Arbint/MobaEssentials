// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueMonitor.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API UValueMonitor : public UUserWidget
{
	GENERATED_BODY()
	public:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageComp;
	
	UFUNCTION(BlueprintCallable, Category="ValueMonitor")
	void SetValue(float value);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ValueMonitor")
	FName AttrName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ValueMonitor")
	class UMaterialInterface* Mtl;
};
