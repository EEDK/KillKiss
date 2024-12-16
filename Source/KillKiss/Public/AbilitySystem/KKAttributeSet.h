// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "KKAttributeSet.generated.h"

USTRUCT(Blueprintable)
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class KILLKISS_API UKKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UKKAttributeSet();

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	//~Begin Vital Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentMana)
	//~End Vital Attribute

	//~Begin Primary Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PriamryAttribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "PriamryAttribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "PriamryAttribute")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Luck)

	UPROPERTY(BlueprintReadOnly, Category = "PriamryAttribute")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "PriamryAttribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Vigor)
	//~End Primary Attribute

	//~Begin Secondary Attribute
	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, ArmorPenetration)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CriticalHitChance)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CriticalHitDamage)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CriticalHitResistance)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, HealthRegeneration)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, ManaRegeneration)

	UPROPERTY(BlueprintReadOnly, Category = "SecondaryAttribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxMana)
	//~End Secondary Attribute

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
