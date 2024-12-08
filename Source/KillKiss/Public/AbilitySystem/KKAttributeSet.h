// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "KKAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class KILLKISS_API UKKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UKKAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentMana)

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxMana)

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
