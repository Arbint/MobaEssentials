// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ValueMonitor.h"
#include "Components/Image.h"
#include "Materials/MaterialInterface.h"

void UValueMonitor::NativeConstruct()
{
	Super::NativeConstruct();
	if (ImageComp)
	{
		ImageComp->SetBrushFromMaterial(Mtl);
	}
}

void UValueMonitor::SetValue(float value)
{
	if (ImageComp)
	{
		ImageComp->GetDynamicMaterial()->SetScalarParameterValue(AttrName, value);
	}
}
