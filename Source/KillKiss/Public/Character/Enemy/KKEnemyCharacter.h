// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KKCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "KKEnemyCharacter.generated.h"

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

protected:
	virtual void BeginPlay() override;

	// ~Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	// ~End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	//~ Begin WidgetController Delegates
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChanged OnMaxHealthChanged;
	//~ End WidgetController Delegates

private:
	void InitEnemyStartUpData() const;

	UPROPERTY(EditAnywhere)
	int32 Level = 1;
};
