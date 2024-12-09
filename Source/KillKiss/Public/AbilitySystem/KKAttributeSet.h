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
/**
 * 
 */
UCLASS()
class KILLKISS_API UKKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UKKAttributeSet();

	//~Begin Vital Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, CurrentMana)

	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, MaxMana)
	//~End Vital Attribute


	//~Begin Primary Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UKKAttributeSet, Luck)
	//~End Primary Attribute

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
