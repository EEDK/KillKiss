// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "KKCharacterBase.generated.h"

class UDataAsset_StartupDataBase;
class UGameplayEffect;
class UAttributeSet;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

UCLASS(Abstract)
class KILLKISS_API AKKCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AKKCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAttributeSet> AttributeSet;

	// Set Attributes Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartupDataBase> CharacterStartUpData;
	//~Set Attributes Data

	virtual void InitAbilityActorInfo();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

private:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* HitReactMontage;

public:
	// ~Begin IAbilitySystemInterface Interface.
	UFUNCTION()
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~End IAbilitySystemInterface Interface

	// ~Begin ICombatInterface Interface.
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	// ~End ICombatInterface Interface

	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}
};
