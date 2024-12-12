// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDataBase.generated.h"

class UGameplayEffect;
class UKKGameplayAbility;
class UKKAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class KILLKISS_API UDataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKKAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1.f);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKKGameplayAbility>> ActivationOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKKGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UKKGameplayAbility>>& InAbilitiesToGive,
	                    UKKAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
