// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/KKPlayerState.h"

#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "AbilitySystem/KKAttributeSet.h"

AKKPlayerState::AKKPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKKAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UKKAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AKKPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
