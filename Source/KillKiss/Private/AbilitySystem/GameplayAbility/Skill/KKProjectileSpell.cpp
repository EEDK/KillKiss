// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/Skill/KKProjectileSpell.h"

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
		FVector SocketLocation;
		if (ComboCount % 2 == 1)
		{
			SocketLocation = CombatInterface->GetLeftHandSocket();
		}
		else
		{
			SocketLocation = CombatInterface->GetRightHandSocket();
		}

		DrawDebugSphere(GetWorld(), SocketLocation, 32.f, 12, FColor::Red, false, 2.f);
	}
}
