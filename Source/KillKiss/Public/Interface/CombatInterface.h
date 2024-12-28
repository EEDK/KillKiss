// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KILLKISS_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();

	virtual FVector GetPlayerWeaponSocket();
	virtual FVector GetLeftHandSocket();
	virtual FVector GetRightHandSocket();

};
