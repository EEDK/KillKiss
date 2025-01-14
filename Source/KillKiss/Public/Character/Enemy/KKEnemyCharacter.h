// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/KKCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "KKEnemyCharacter.generated.h"

class AKKAIController;
class UBehaviorTree;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class KILLKISS_API AKKEnemyCharacter : public AKKCharacterBase
{
	GENERATED_BODY()

public:
	AKKEnemyCharacter();
	// ~Begin IAbilitySystemInterface Interface.
	virtual int32 GetPlayerLevel() override;
	// ~End IAbilitySystemInterface Interface

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AKKAIController> KKAIController;

	//~ Begin WidgetController Delegates
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChanged OnMaxHealthChanged;
	//~ End WidgetController Delegates

private:
	void BindHealthChangeCallbacks();
};
