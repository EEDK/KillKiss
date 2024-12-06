// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KKCharacterBase.h"
#include "KKPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class KILLKISS_API AKKPlayerCharacter : public AKKCharacterBase
{
	GENERATED_BODY()

public:
	AKKPlayerCharacter();

protected:

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> FollowCamera;
};
