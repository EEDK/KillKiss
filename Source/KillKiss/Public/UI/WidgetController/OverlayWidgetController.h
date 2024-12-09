// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, const float& /*Attribute*/);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KILLKISS_API UOverlayWidgetController : public UKKWidgetController
{
	GENERATED_BODY()

public:
	FOnAttributeChanged OnHealthChanged;
	FOnAttributeChanged OnMaxHealthChanged;
	FOnAttributeChanged OnManaChanged;
	FOnAttributeChanged OnMaxManaChanged;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
};
