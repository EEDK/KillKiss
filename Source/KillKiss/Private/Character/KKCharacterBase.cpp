// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KKCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AKKCharacterBase::AKKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AKKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AKKCharacterBase::InitAbilityActorInfo()
{
}

void AKKCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const
{
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent();
	check(TargetASC);
	check(GameplayEffectClass);

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, 1.f, EffectContextHandle);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AKKCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

UAbilitySystemComponent* AKKCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
