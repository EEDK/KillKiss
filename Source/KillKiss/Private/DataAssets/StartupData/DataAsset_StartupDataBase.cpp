// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"

#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "AbilitySystem/GameplayAbility/KKGameplayAbility.h"
#include "Character/KKCharacterBase.h"

void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(UKKAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivationOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass)
			{
				continue;
			}
			FGameplayEffectContextHandle EffectContextHandle = InASCToGive->MakeEffectContext();

			const AKKCharacterBase* Character = Cast<AKKCharacterBase>(InASCToGive->GetAvatarActor());
			EffectContextHandle.AddSourceObject(Character);

			const UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, EffectContextHandle);
		}
	}
}


void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UKKGameplayAbility>>& InAbilitiesToGive,
                                                UKKAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UKKGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
