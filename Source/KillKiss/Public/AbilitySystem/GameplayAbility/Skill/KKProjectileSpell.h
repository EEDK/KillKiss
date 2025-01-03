// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/KKGameplayAbility.h"
#include "KKProjectileSpell.generated.h"

class AKKProjectile;
/**
 * 
 */
UCLASS()
class KILLKISS_API UKKProjectileSpell : public UKKGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AKKProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	// 스킬의 Damage 속성을 저장하는 ScalableFloat
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FScalableFloat Damage;


	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnFireBall();

private:
	UPROPERTY(BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	int32 ComboCount = 1;
};
