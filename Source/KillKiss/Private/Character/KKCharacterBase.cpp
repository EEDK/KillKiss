// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KKCharacterBase.h"

AKKCharacterBase::AKKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKKCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKKCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
