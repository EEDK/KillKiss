// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KKGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EKKAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};


/**
 * 
 */
UCLASS()
class KILLKISS_API UKKGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	// ~Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	// ~End UGameplayAbility Interface.


	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EKKAbilityActivationPolicy AbilityActivationPolicy = EKKAbilityActivationPolicy::OnTriggered;


private:
	
};