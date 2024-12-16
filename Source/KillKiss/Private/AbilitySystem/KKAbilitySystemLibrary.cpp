// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KKAbilitySystemLibrary.h"

#include "Character/Player/KKPlayerState.h"
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
