// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KKPlayerController.generated.h"

class UDamageTextComponent;
/**
 * 
 */
UCLASS()
class KILLKISS_API AKKPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
