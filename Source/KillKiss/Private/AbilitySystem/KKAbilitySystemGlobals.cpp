// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KKAbilitySystemGlobals.h"

#include "KKAbilityTypes.h"

FGameplayEffectContext* UKKAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FKKGameplayEffectContext();
}
