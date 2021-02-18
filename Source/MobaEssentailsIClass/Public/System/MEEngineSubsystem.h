// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "MEEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MOBAESSENTAILSICLASS_API UMEEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
