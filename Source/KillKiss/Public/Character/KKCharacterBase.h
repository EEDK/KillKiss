// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KKCharacterBase.generated.h"


UCLASS()
class KILLKISS_API AKKCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AKKCharacterBase();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

public:
};
