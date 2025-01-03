// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/Skill/KKProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "KKGameplayTags.h"
#include "Actor/KKProjectile.h"
#include "Interface/CombatInterface.h"

void UKKProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKKProjectileSpell::SpawnFireBall()
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetLeftHandSocket();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorRotation().Quaternion());

		AKKProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKKProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		UAbilitySystemComponent* SourceASC =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle =
			SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		const float ScaledDamage = Damage.GetValueAtLevel(10);

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, KKGameplayTags::Damage, ScaledDamage);

		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
