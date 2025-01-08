// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KKAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "KKDebugHelper.h"
#include "KKGameplayTags.h"
#include "AbilitySystem/KKAbilitySystemLibrary.h"
#include "Controllers/KKPlayerController.h"
#include "GameFramework/Character.h"

UKKAttributeSet::UKKAttributeSet()
{
	//~Begin Primary Attribute
	TagsToAttributes.Add(KKGameplayTags::Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Primary_Luck, GetLuckAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Primary_DefensePower, GetDefensePowerAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Primary_Vigor, GetVigorAttribute);
	//~End Primary Attribute

	//~Begin Secondary Attribute
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(KKGameplayTags::Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	//~Begin End Attribute
}

void UKKAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetCurrentManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UKKAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	{
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetCurrentHealth() - LocalIncomingDamage;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(KKGameplayTags::Shared_Ability_HitPause);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			const bool bBlockedHit = UKKAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
			const bool bCriticalHit = UKKAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);

			ShowFloatingText(Props, LocalIncomingDamage, bBlockedHit, bCriticalHit);
		}
	}
}

void UKKAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) &&
		Props.SourceASC->AbilityActorInfo.IsValid() &&
		Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() &&
		Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UKKAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit,
                                       bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AKKPlayerController* PC = Cast<AKKPlayerController>(Props.SourceController))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}
	}
}
