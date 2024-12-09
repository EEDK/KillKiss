// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/KKAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UKKAttributeSet* KKAttributeSet = CastChecked<UKKAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(KKAttributeSet->GetCurrentHealth());
	OnMaxHealthChanged.Broadcast(KKAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(KKAttributeSet->GetCurrentMana());
	OnMaxManaChanged.Broadcast(KKAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UKKAttributeSet* KKAttributeSet = CastChecked<UKKAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KKAttributeSet->GetCurrentHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KKAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KKAttributeSet->GetCurrentManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KKAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
}
