// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "KKInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class KILLKISS_API UKKInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
inline void UKKInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                     const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
                                                     UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can't bind"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}
