// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KILLKISS_API UAttributeMenuWidgetController : public UKKWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
};
