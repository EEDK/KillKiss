// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KKCharacter.h"

AKKCharacter::AKKCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKKCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
