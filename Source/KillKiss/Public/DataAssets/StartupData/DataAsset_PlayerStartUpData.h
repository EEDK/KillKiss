// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartupDataBase.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/GameplayAbility/KKGameplayAbility.h"
#include "DataAsset_PlayerStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKKGameplayAbility> AbilityToGrant;

	bool IsValid() const
	{
		return InputTag.IsValid() && *AbilityToGrant != nullptr;
	}
};

/**
 * 
 */
UCLASS()
class KILLKISS_API UDataAsset_PlayerStartUpData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKKAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<FPlayerAbilitySet> PlayerStartUpAbilitySets;
};
