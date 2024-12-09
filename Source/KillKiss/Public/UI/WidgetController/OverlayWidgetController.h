// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, NewValue /*Attribute*/);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KILLKISS_API UOverlayWidgetController : public UKKWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChanged OnMaxManaChanged;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
};
