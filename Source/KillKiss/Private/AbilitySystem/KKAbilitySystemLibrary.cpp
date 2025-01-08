// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KKAbilitySystemLibrary.h"

#include "KKAbilityTypes.h"
#include "Character/Player/KKPlayerState.h"
#include "GameMode/KKGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/KKHUD.h"
#include "UI/WidgetController/KKWidgetController.h"

UOverlayWidgetController* UKKAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		if (AKKHUD* KKHUD = Cast<AKKHUD>(PC->GetHUD()))
		{
			AKKPlayerState* PS = PC->GetPlayerState<AKKPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WCParms(PC, PS, ASC, AS);

			return KKHUD->GetOverlayWidgetController(WCParms);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UKKAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		if (AKKHUD* KKHUD = Cast<AKKHUD>(PC->GetHUD()))
		{
			AKKPlayerState* PS = PC->GetPlayerState<AKKPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WCParms(PC, PS, ASC, AS);

			return KKHUD->GetAttributeMenuWidgetController(WCParms);
		}
	}

	return nullptr;
}

UCurveTable* UKKAbilitySystemLibrary::GetDamageCalculationCoefficients(const UObject* WorldContextObject)
{
	const AKKGameModeBase* KKGameModeBase
		= Cast<AKKGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));

	if (!KKGameModeBase)
	{
		return nullptr;
	}

	return KKGameModeBase->DamageCalculationCoefficients;
}

bool UKKAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKKGameplayEffectContext* KKEffectContext =
		static_cast<const FKKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KKEffectContext->IsBlockedHit();
	}

	return false;
}

bool UKKAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKKGameplayEffectContext* KKEffectContext =
		static_cast<const FKKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KKEffectContext->IsCriticalHit();
	}

	return false;
}

void UKKAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FKKGameplayEffectContext* KKEffectContext = static_cast<FKKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KKEffectContext->SetBlockedHit(bInIsBlockedHit);
	}
}

void UKKAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FKKGameplayEffectContext* KKEffectContext = static_cast<FKKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KKEffectContext->SetCriticalHit(bInIsCriticalHit);
	}
}
