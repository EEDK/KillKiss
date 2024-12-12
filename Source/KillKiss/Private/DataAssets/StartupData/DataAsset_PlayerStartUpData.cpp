// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_PlayerStartUpData.h"

#include "AbilitySystem/KKAbilitySystemComponent.h"

void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UKKAbilitySystemComponent* InASCToGive,
                                                                int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilitySet.AbilityToGrant.Get());
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
