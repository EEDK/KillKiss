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

UAbilitySystemComponent* AKKCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
