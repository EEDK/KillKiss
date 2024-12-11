// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "KKPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class KILLKISS_API AKKPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKKPlayerState();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	int32 PlayerLevel = 1.f;

public:
	// ~Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~End IAbilitySystemInterface Interface

	UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
};
