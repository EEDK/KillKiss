// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KKCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "KillKiss/KillKiss.h"

AKKCharacterBase::AKKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
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
