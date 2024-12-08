// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KKAttributeSet.h"

UKKAttributeSet::UKKAttributeSet()
{
	InitCurrentHealth(50.f);
	InitMaxHealth(100.f);

	InitCurrentMana(25.f);
	InitMaxMana(50.f);
}

void UKKAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetCurrentManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UKKAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}
